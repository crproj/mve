#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <limits.h>
#include <sstream>
#include <fstream>
#include <util/file_system.h>

#include <QtGui>
#include <QtCore>
#include <QPushButton>
#include <QGroupBox>
#include <QDebug>
#include <QColorDialog>
#include <QAction>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QGraphicsOpacityEffect>

#include "addin_manager.h"
#include "scenemanager.h"
#include "sceneoverview.h"
#include "regioning_plugin.h"
#include "mve/image.h"
#include "mve/image_io.h"
#include "mve/image_tools.h"

#include <iostream>
#include <fstream>
//#include "utils.h"

#include "adverror.h"
#include "advstr.h"
#include "ipcmatrix.h"
#include "ipccolor.h"
#include "ipcxpmfile.h"
#include "ipcstdhsvlinkcontrol.h"
#include "ipcstdrgblinkcontrol.h"
#include "ipctrafficsignlinkcontrol.h"
#include "ipccsc.h"

/* This defines the directory which is used to store debugging information (i.e. images), starting relatively
 * from your home directory. Set this to "/" if you want to save them directly into your home directory */
#define RELATIVE_DEBUG_DIR "/img/ppm/"
#define CREATE_DEBUG_IMAGES 0



RegioningPlugin::RegioningPlugin(QWidget *parent) : MainWindowTab(parent), create_debug_images(true) {
	QVBoxLayout *vbox = new QVBoxLayout(this);

	/* Create new toolbar with icons (and fallbacks) */
	this->toolbar = new QToolBar(this);
	RegioningPlugin::quads = std::vector<Quadrangle>();
	RegioningPlugin::currentq = Quadrangle();
	RegioningPlugin::editmode = false;
	this->color_dialog = new QColorDialog();
	this->spinbox_region_id_label = new QLabel("Region ID");
	this->spinbox_region_id = new QSpinBox();

	/* Create actions */
	this->save_view = new QAction(QIcon(":/img/icon_save.png"), tr("Save regions for this view"), this);
	this->edit_area = new QAction(QIcon(":/img/edit.png"), tr("Move area points"), this);
	this->polycompl = new QAction(QIcon(":/img/polycompl.png"), tr("Complete this polygon"), this);
	this->action_zoom_in = new QAction(QIcon(":/img/icon_zoom_in.svg"), tr("Zoom in"), this);
	this->action_zoom_out = new QAction(QIcon(":/img/icon_zoom_out.svg"), tr("Zoom out"), this);
	this->action_zoom_reset = new QAction(QIcon(":/img/icon_zoom_reset.svg"), tr("Reset zoom"), this);
	this->action_zoom_fit = new QAction(QIcon(":/img/icon_zoom_page.svg"), tr("Fit to window"), this);
	this->action_zoom_fit->setCheckable(true);
	this->edit_area->setCheckable(true);
	this->scroll_image = new ScrollImage();
	this->update_actions();


  	/* Create details notebook. */
  	this->tab_widget = new QTabWidget();
    	this->tab_widget->setTabPosition(QTabWidget::East);
   	/* Create GL context. */
   	this->gl_widget = new GLWidget();
   	this->addin_manager = new AddinManager(this->gl_widget, this->tab_widget);
   	this->gl_widget->set_context(this->addin_manager);
    	//QVBoxLayout* vbox2 = new QVBoxLayout();
    	vbox->addWidget(toolbar);


	/*==============
	* Default values
	* ==============*/
	/* Maximum euclidean distance in RGB is approximately 442 */

	this->spinbox_region_id->setMinimum(0);
	this->spinbox_region_id->setMaximum(7);
	this->spinbox_region_id->setToolTip(tr("Region ID"));
	this->spinbox_region_id->setValue(0);
	this->color_dialog->setModal(1);

	/* Add icons, tooltips, parent information to toolbar */
	this->toolbar->addAction(this->action_zoom_in);
	this->toolbar->addAction(this->action_zoom_out);
	this->toolbar->addAction(this->action_zoom_reset);
	this->toolbar->addAction(this->action_zoom_fit);
	this->toolbar->addAction(this->polycompl);
	this->toolbar->addAction(this->save_view);
	this->toolbar->addAction(this->edit_area);
	this->toolbar->addWidget(this->spinbox_region_id);
	this->toolbar->addWidget(this->spinbox_region_id_label);


	/*=======================
	* Alignment, signals/slots
	* ========================*/
	toolbar->setGeometry(10, 10, 200, 30);
	vbox->addWidget(toolbar);
	vbox->addWidget(this->scroll_image);

	connect(this->save_view, SIGNAL(triggered()), this, SLOT(handle_save_view()));
	connect(this->edit_area, SIGNAL(triggered()), this, SLOT(handle_edit_area()));
	connect(this->polycompl, SIGNAL(triggered()), this, SLOT(handle_polycompl()));
	connect(&SceneManager::get(), SIGNAL(view_selected(mve::View::Ptr)), this, SLOT(receive_view_pointer(mve::View::Ptr)));
	connect(this->scroll_image->get_image(), SIGNAL(mouse_clicked(int, int, QMouseEvent *)), this, SLOT(on_image_clicked(int, int, QMouseEvent *)));
	connect(this->scroll_image->get_image(), SIGNAL(mouse_moved(int, int, QMouseEvent *)), this, SLOT(on_image_moved(int, int, QMouseEvent *)));
	connect(this->scroll_image->get_image(), SIGNAL(mouse_released(int, int, QMouseEvent *)), this, SLOT(on_image_released(int, int, QMouseEvent *)));
	connect(this->action_zoom_in, SIGNAL(triggered()), this, SLOT(on_zoom_in()));
	connect(this->action_zoom_out, SIGNAL(triggered()), this, SLOT(on_zoom_out()));
	connect(this->action_zoom_reset, SIGNAL(triggered()), this, SLOT(on_normal_size()));
	connect(this->action_zoom_fit, SIGNAL(triggered()), this, SLOT(on_fit_to_window()));
	connect(&SceneManager::get(), SIGNAL(scene_selected(mve::Scene::Ptr)), this, SLOT(on_scene_selected()));

    	this->connect(this, SIGNAL(tab_activated()), SLOT(on_tab_activated()));

	/* TODO: Make this configurable */
	this->create_debug_images = CREATE_DEBUG_IMAGES;

    	QHBoxLayout* main_layout = new QHBoxLayout(this);
    	main_layout->addLayout(vbox, 1);
    	main_layout->addWidget(this->tab_widget);
}


void RegioningPlugin::handle_polycompl() {

//TODO

}



void RegioningPlugin::handle_edit_area() {
    editmode = this->edit_area->isChecked();
    std::cout << "Editmode: " << editmode << std::endl;
}


void RegioningPlugin::handle_save_view() {
	mve::View::Ptr view = this->current_view_pointer;

	/* Save results */
	std::string filename = view->get_filename().substr(0,view->get_filename().size()-3)+"rgn";
	ofstream out(filename);

	for (unsigned int i = 0; i < quads.size(); i++) {
	    if (quads[i].isComplete()) {
		out << quads[i].getID() << "\r\n";
		out << quads[i].xCoords[0] << "\r\n" << quads[i].yCoords[0] << "\r\n";
		out << quads[i].xCoords[1] << "\r\n" << quads[i].yCoords[1] << "\r\n";
		out << quads[i].xCoords[2] << "\r\n" << quads[i].yCoords[2] << "\r\n";
		out << quads[i].xCoords[3] << "\r\n" << quads[i].yCoords[3] << "\r\n";
	    }
	}
	out.close();
}


void RegioningPlugin::on_image_clicked(int x, int y, QMouseEvent *event) {
	
	/* Which buttons have been pressed? */
	bool left_click = event->buttons() & Qt::LeftButton;
	bool right_click = event->buttons() & Qt::RightButton;
	float xf, yf;
	xf = ((float) x) / current_view_pointer->get_image("original")->width();
	yf = ((float) y) / current_view_pointer->get_image("original")->height();
	std::cout << xf << ", " << yf << std::endl;
	if (left_click) {
	    if (!editmode) {
		if( !currentq.isComplete() ){
			currentq.addPoint( xf, yf);
			currentq.setID(this->spinbox_region_id->value());
			if (currentq.isComplete()) {
			mve::ByteImage::Ptr overlay = this->current_view_pointer->get_image("original");
			QImage *q_img_overlay = new QImage(overlay->width(), overlay->height(), QImage::Format_RGB32);
			QPixmap pixmap_overlay(QPixmap::fromImage(*q_img_overlay));
			delete q_img_overlay;
			transparent = QPixmap(pixmap_overlay.size());
			transparent.fill(Qt::transparent);

			bool exists = false;

			for (unsigned int i = 0; i < quads.size(); i++) {
			    if (this->spinbox_region_id->value() == quads[i].getID())
				exists = true;
			}

			if (!exists)
			    quads.push_back(currentq);

			for (unsigned int i = 0; i < quads.size(); i++)
				drawPoly(&quads[i]);

			this->spinbox_region_id->setValue(this->spinbox_region_id->value()+1);

			RegioningPlugin::currentq = Quadrangle();
			}
		}
	    } else {

	//TODO Logic for editing
	//
	//if (in der naehe von 10 px, suche naechsten punkt yum verschieben
	//
	//Draggen

	    }
	}
	if (right_click) {

	//TODO Evtl Punkte entfernen??

	}
}


void RegioningPlugin::drawPoly (Quadrangle* q) {

			mve::ByteImage::Ptr base = this->current_view_pointer->get_image("original");
			mve::ByteImage::Ptr overlay = this->current_view_pointer->get_image("original");
			QImage *q_img_base = new QImage(base->width(), base->height(), QImage::Format_RGB32);
			QImage *q_img_overlay = new QImage(overlay->width(), overlay->height(), QImage::Format_RGB32);
			QColor qc = QColor(204,204,204,125);
		
			if (q->getID() == 0)
				qc = QColor(0,204,0,125);
			if (q->getID() == 1)
				qc = QColor(0,0,204,125);
			if (q->getID() == 2)
				qc = QColor(204,0,0,125);
			if (q->getID() == 3)
				qc = QColor(204,204,0,125);
			if (q->getID() == 4)
				qc = QColor(0,204,204,125);
			if (q->getID() == 5)
				qc = QColor(204,0,204,125);
			if (q->getID() == 6)
				qc = QColor(102,102,0,125);
			if (q->getID() == 7)
				qc = QColor(204,204,204,125);

			QPointF points[4] = {
 			    QPointF(q->xCoords[0]*overlay->width(), q->yCoords[0]*overlay->height()),
 			    QPointF(q->xCoords[1]*overlay->width(), q->yCoords[1]*overlay->height()),
  			    QPointF(q->xCoords[2]*overlay->width(), q->yCoords[2]*overlay->height()),
  			    QPointF(q->xCoords[3]*overlay->width(), q->yCoords[3]*overlay->height())
 			};


			this->mve2qt(base, q_img_base);
			this->mve2qt(overlay, q_img_overlay);
			QPixmap pixmap_base(QPixmap::fromImage(*q_img_base));
			QPixmap pixmap_overlay(QPixmap::fromImage(*q_img_overlay));
			delete q_img_base;
			delete q_img_overlay;

			/* Apply transparency */
			QPainter p(&transparent);
			p.setCompositionMode(QPainter::CompositionMode_SourceOver);
			p.setBrush(QBrush(qc));
			p.setPen(qc);
			p.drawPolygon(points, 4, Qt::WindingFill);
			p.end();

			/* Draw overlay on top of base image */
			QPainter painter(&pixmap_base);
			painter.drawPixmap(0, 0, transparent);
			display_image(&pixmap_base);
}

void
RegioningPlugin::on_details_toggled (void)
{
    bool show = this->action_show_details->isChecked();
    this->tab_widget->setVisible(show);
}

bool RegioningPlugin::display_result() {
	//TODO brauchen wir die Funktion?
    return true;
}

void RegioningPlugin::update_actions(void) {
	bool active = this->scroll_image->get_pixmap() != NULL;
	bool fit = this->action_zoom_fit->isChecked();
	this->action_zoom_fit->setEnabled(active);
	this->action_zoom_in->setEnabled(active && !fit);
	this->action_zoom_out->setEnabled(active && !fit);
	this->action_zoom_reset->setEnabled(active && !fit);
}

/* Takes a QImage and displays it in UMVE */
void RegioningPlugin::display_image(QPixmap *pixmap) {
	this->scroll_image->set_pixmap(*pixmap);
	this->update_actions();
}
/* Takes a QImage and displays it in UMVE */
void RegioningPlugin::display_image(QImage *q_img) {
	QPixmap pixmap = QPixmap::fromImage(*q_img);
	this->display_image(&pixmap);
}

/* Displays an image with all of its regions*/
void RegioningPlugin::display_image(mve::ByteImage::ConstPtr img) {
	QImage *q_img = new QImage(img->width(), img->height(), QImage::Format_RGB32);
	this->mve2qt(img, q_img);
	this->display_image(q_img);
//TODO polygone incomplete
	ifstream myfile;
	std::string filename = current_view_pointer->get_filename().substr(0,current_view_pointer->get_filename().size()-3)+"rgn";
	myfile.open (filename, ios::in);
	if (myfile.is_open()) {
		char buf[50];
		while (!myfile.eof()) {
			Quadrangle q = Quadrangle();
			myfile.getline(buf, 50);
			int id = atoi (buf);
			q.setID(id);
			for (int i=0; i<4; i++) {
				if (!myfile.eof()) {
    		    			myfile.getline(buf, 50);
		   			float x = atof(buf);
		    			myfile.getline(buf, 50);
		    			float y = atof(buf);
		    			if (!(q.isComplete())) {
	    					q.addPoint(x,y);
						if (q.isComplete()) {
							mve::ByteImage::Ptr overlay = this->current_view_pointer->get_image("original");
							QImage *q_img_overlay = new QImage(overlay->width(), overlay->height(), QImage::Format_RGB32);
							QPixmap pixmap_overlay(QPixmap::fromImage(*q_img_overlay));
							delete q_img_overlay;
							transparent = QPixmap(pixmap_overlay.size());
							transparent.fill(Qt::transparent);

							quads.push_back(q);
						}
	    				}
				}				
			}
		}
	}


	for (unsigned int i = 0; i < quads.size(); i++)
		drawPoly(&quads[i]);

	delete q_img;
}

/* Both receives and handles the view pointer that SceneManager emits */
void RegioningPlugin::receive_view_pointer(mve::View::Ptr view_pointer) {

	RegioningPlugin::quads = std::vector<Quadrangle>();
	RegioningPlugin::currentq = Quadrangle();

	if (view_pointer != NULL) {
		this->current_view_pointer = view_pointer;
		this->current_image_pointer = view_pointer->get_byte_image("original");
	}

	this->transform_view_pointer(view_pointer);
}

/* This function will handle a view pointer and make it usable for Qt */
void RegioningPlugin::transform_view_pointer(mve::View::Ptr view_pointer) {
	if (view_pointer != NULL) {
		mve::ByteImage::Ptr img = view_pointer->get_byte_image("original");
		this->current_image_pointer = img;
		this->display_best();
	}
}

void RegioningPlugin::on_zoom_in(void) {
	this->scroll_image->zoom_in();
}
void RegioningPlugin::on_zoom_out(void) {
	this->scroll_image->zoom_out();
}
void RegioningPlugin::on_normal_size(void) {
	this->scroll_image->reset_scale();
}
void RegioningPlugin::on_fit_to_window(void) {
	bool fit = this->action_zoom_fit->isChecked();
	this->scroll_image->set_auto_scale(fit);
	this->update_actions();
}

/* Converts an mve::ByteImage::Ptr to a QImage */
void RegioningPlugin::mve2qt(mve::ByteImage::ConstPtr src, QImage *dest) {
	std::size_t image_width = src->width();
	std::size_t image_height = src->height();

	if (src->channels() == 3) {
		#pragma omp parallel for collapse(2)
		for (std::size_t y = 0; y < image_height; ++y) {
			for (std::size_t x = 0; x < image_width; ++x) {
				unsigned int r = (unsigned int)(src->at(x, y, 0));
				unsigned int g = (unsigned int)(src->at(x, y, 1));
				unsigned int b = (unsigned int)(src->at(x, y, 2));
				unsigned int rgb = r << 16 | g << 8 | b;
				dest->setPixel(x, y, rgb);
			}
		}
	}
	else
		if (src->channels() == 1) {
			/* One-channel images */
			#pragma omp parallel for collapse(2)
			for (std::size_t y = 0; y < image_height; ++y)
				for (std::size_t x = 0; x < image_width; ++x) {
					unsigned int val = (unsigned int)(src->at(x, y, 0));
					unsigned int r = val ? 255 : 0;
					unsigned int g = val ? 0   : 0;
					unsigned int b = val ? 255 : 0;
					unsigned int rgb = r << 16 | g << 8 | b;
					dest->setPixel(x, y, rgb);
				}
		}
}

void RegioningPlugin::display_original() {
	if (this->current_image_pointer != NULL)
		this->display_image(this->current_image_pointer);
}


void RegioningPlugin::display_best() {
	//if (this->display_result() == false)
		this->display_original();
}

RegioningPlugin::~RegioningPlugin() {
	//this->results.clear();
}

QString RegioningPlugin::get_title() {
	return tr("Regioning");
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(RegioningPlugin, RegioningPlugin)
#endif
