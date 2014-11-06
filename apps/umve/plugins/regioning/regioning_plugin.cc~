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


	odd = false;

	/* Create new toolbar with icons (and fallbacks) */
	this->toolbar = new QToolBar(this);
	// QAction *colorButton = new QAction(QIcon::fromTheme("", QIcon(":/img/chroma.png")), tr("Select chroma key"), this);
    //QToolBar* toolbar2 = new QToolBar("Mesh tools");
    this->create_actions(toolbar);
	//TODO
	q1 = new Quadrangle(1);
	q2 = new Quadrangle(2);

	this->color_dialog = new QColorDialog();

	this->spinbox_region_id_label = new QLabel("Region ID");
	this->spinbox_region_id = new QSpinBox();

	/* Create actions */
	this->save_view = new QAction(QIcon(":/img/icon_save.svg"), tr("Test"), this);
	this->save_all_views = new QAction(QIcon(":/img/icon_save_all.svg"), tr("Save all sky masks as embedding"), this);
	this->button_apply = new QAction(QIcon(":/img/folder-drag-accept.png"), tr("Compute mask"), this);
	this->button_apply_all = new QAction(QIcon(":/img/apply-all.png"), tr("Compute mask for all"), this);
	this->button_apply_to_depth_map = new QAction(QIcon(":/img/apply_to_depth_map.png"), tr("Apply mask to single depth map and save"), this);
	this->button_apply_to_all_depth_maps = new QAction(QIcon(":/img/apply_to_all_depth_maps.png"), tr("Apply masks to all depth maps and save"), this);
	this->action_zoom_in = new QAction(QIcon(":/img/icon_zoom_in.svg"), tr("Zoom in"), this);
	this->action_zoom_out = new QAction(QIcon(":/img/icon_zoom_out.svg"), tr("Zoom out"), this);
	this->action_zoom_reset = new QAction(QIcon(":/img/icon_zoom_reset.svg"), tr("Reset zoom"), this);
	this->action_zoom_fit = new QAction(QIcon(":/img/icon_zoom_page.svg"), tr("Fit to window"), this);
	this->action_zoom_fit->setCheckable(true);



	this->scroll_image = new ScrollImage();

	this->update_actions();


  	  /* Create details notebook. */
  	  this->tab_widget = new QTabWidget();
    	this->tab_widget->setTabPosition(QTabWidget::East);
	this->scroll_image2 = new ScrollImage();
   	 /* Create GL context. */
   	 this->gl_widget = new GLWidget();
   	 this->addin_manager = new AddinManager(this->gl_widget, this->tab_widget);
   	 //this->gl_widget->set_context(this->addin_manager);
    //QVBoxLayout* vbox2 = new QVBoxLayout();
    vbox->addWidget(toolbar);
    vbox->addWidget(this->scroll_image2);


	/*==============
	* Default values
	* ==============*/
	/* Maximum euclidean distance in RGB is approximately 442 */

	this->spinbox_region_id->setMinimum(0);
	this->spinbox_region_id->setMaximum(INT_MAX);
	this->spinbox_region_id->setToolTip(tr("Region ID"));
	this->spinbox_region_id->setValue(0);

	/* TODO: */
	//color_dialog->setCurrentColor(getSkyColor());
	this->color_dialog->setModal(1);

	/* Add icons, tooltips, parent information to toolbar */
	//toolbar->addAction(colorButton);
	this->toolbar->addAction(this->action_zoom_in);
	this->toolbar->addAction(this->action_zoom_out);
	this->toolbar->addAction(this->action_zoom_reset);
	this->toolbar->addAction(this->action_zoom_fit);

	this->toolbar->addAction(this->button_apply);
	this->toolbar->addAction(this->button_apply_all);
	this->toolbar->addAction(this->save_view);
	this->toolbar->addAction(this->save_all_views);
	this->toolbar->addAction(this->button_apply_to_depth_map);
	this->toolbar->addAction(this->button_apply_to_all_depth_maps);

	this->toolbar->addWidget(this->spinbox_region_id);
	this->toolbar->addWidget(this->spinbox_region_id_label);

	/* Create new image and set zoom actions */


	/*=======================
	* Alignment, signals/slots
	* ========================*/
	toolbar->setGeometry(10, 10, 200, 30);
	vbox->addWidget(toolbar);
	vbox->addWidget(this->scroll_image);

	//connect(colorButton, SIGNAL(triggered()), color_dialog, SLOT(show()));
	connect(this->save_view, SIGNAL(triggered()), this, SLOT(handle_save_view()));
	connect(this->save_all_views, SIGNAL(triggered()), this, SLOT(handle_save_all_views()));
	connect(this->button_apply, SIGNAL(triggered()), this, SLOT(handle_apply()));
	connect(this->button_apply_all, SIGNAL(triggered()), this, SLOT(handle_apply_all()));
	connect(this->button_apply_to_depth_map, SIGNAL(triggered()), this, SLOT(handle_apply_to_depth_map()));
	connect(this->button_apply_to_all_depth_maps, SIGNAL(triggered()), this, SLOT(handle_apply_to_all_depth_maps()));
	connect(&SceneManager::get(), SIGNAL(view_selected(mve::View::Ptr)), this, SLOT(receive_view_pointer(mve::View::Ptr)));
	connect(this->scroll_image->get_image(), SIGNAL(mouse_clicked(int, int, QMouseEvent *)), this, SLOT(on_image_clicked(int, int, QMouseEvent *)));
	connect(this->scroll_image->get_image(), SIGNAL(mouse_moved(int, int, QMouseEvent *)), this, SLOT(on_image_moved(int, int, QMouseEvent *)));
	connect(this->scroll_image->get_image(), SIGNAL(mouse_released(int, int, QMouseEvent *)), this, SLOT(on_image_released(int, int, QMouseEvent *)));


	connect(this->scroll_image2->get_image(), SIGNAL(mouse_clicked(int, int, QMouseEvent *)), this, SLOT(on_image_clicked(int, int, QMouseEvent *)));
	connect(this->scroll_image2->get_image(), SIGNAL(mouse_moved(int, int, QMouseEvent *)), this, SLOT(on_image_moved(int, int, QMouseEvent *)));
	connect(this->scroll_image2->get_image(), SIGNAL(mouse_released(int, int, QMouseEvent *)), this, SLOT(on_image_released(int, int, QMouseEvent *)));

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


void RegioningPlugin::handle_save_view() {
	//console.set_sender("hdlsave1");
	mve::View::Ptr view = this->current_view_pointer;

	/*if (view == NULL) {
		console.log("Could not save view because no view has been selected.", "red");
		console.reset_sender();
		return;
	}*/

	/* Save results */
	//this->save_new_embeddings(view, result->sky_detection, result->segmentation);
	//result->has_changed = false;
	//std::stringstream ss;
	//ss << "Successfully saved view: " << view->get_id();
	//console.log(ss.str(), "green");
	//console.reset_sender();
	std::string filename = view->get_filename().substr(0,view->get_filename().size()-3)+"rgn";
	ofstream out(filename);
	out << this->q1->xCoords[0] << ", " << this->q1->yCoords[0] << "\r\n";
	out << this->q1->xCoords[1] << ", " << this->q1->yCoords[1] << "\r\n";
	out << this->q1->xCoords[2] << ", " << this->q1->yCoords[2] << "\r\n";
	out << this->q1->xCoords[3] << ", " << this->q1->yCoords[3];
	out.close();
}


void RegioningPlugin::on_image_clicked(int x, int y, QMouseEvent *event) {
	
	/* Which buttons have been pressed? */
	bool left_click = event->buttons() & Qt::LeftButton;
	bool right_click = event->buttons() & Qt::RightButton;
	std::cout << x << ", " << y << std::endl;
	if (left_click) {
		if( !q1->isComplete() ){
			q1->addPoint( x, y);
			if (q1->isComplete())
				this->spinbox_region_id->setValue(this->spinbox_region_id->value()+1);
		}
		else {
			q2->addPoint(x,y);
		}
	}
	if (right_click) {
		//this->toggle_segment(result, segment_id, false);
		//display_result();
	}
}

void
RegioningPlugin::create_actions (QToolBar* toolbar2)
{
    /*this->action_open_mesh = new QAction(QIcon(":/images/icon_open_file.svg"),
        tr("Open mesh"), this);
    this->connect(this->action_open_mesh, SIGNAL(triggered()),
        this, SLOT(on_open_mesh()));

    this->action_reload_shaders = new QAction(QIcon(":/images/icon_revert.svg"),
        tr("Reload shaders"), this);
    this->connect(this->action_reload_shaders, SIGNAL(triggered()),
        this, SLOT(on_reload_shaders()));*/

    this->action_show_details = new QAction
        (QIcon(":/images/icon_toolbox.svg"), tr("Show &Details"), this);
    this->action_show_details->setCheckable(true);
    this->action_show_details->setChecked(true);
    this->connect(this->action_show_details, SIGNAL(triggered()),
        this, SLOT(on_details_toggled()));

   /* this->action_save_screenshot = new QAction(QIcon(":/images/icon_screenshot.svg"),
        tr("Save Screenshot"), this);
    this->connect(this->action_save_screenshot, SIGNAL(triggered()),
        this, SLOT(on_save_screenshot()));*/

    //toolbar->addAction(this->action_open_mesh);
    //toolbar->addAction(this->action_reload_shaders);
    //toolbar->addSeparator();
    //toolbar->addAction(this->action_save_screenshot);
    toolbar2->addWidget(get_expander());
    toolbar2->addAction(this->action_show_details);
}

void
RegioningPlugin::on_details_toggled (void)
{
    bool show = this->action_show_details->isChecked();
    this->tab_widget->setVisible(show);
}

bool RegioningPlugin::display_result() {
	//TODO
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
	if (!odd) {
	this->scroll_image->set_pixmap(*pixmap);
	odd=true;
	}
	else {
	this->scroll_image2->set_pixmap(*pixmap);
	odd=false;
	}
	this->update_actions();
}
/* Takes a QImage and displays it in UMVE */
void RegioningPlugin::display_image(QImage *q_img) {
	QPixmap pixmap = QPixmap::fromImage(*q_img);
	this->display_image(&pixmap);
}

/* Displays an image */
void RegioningPlugin::display_image(mve::ByteImage::ConstPtr img) {
	QImage *q_img = new QImage(img->width(), img->height(), QImage::Format_RGB32);
	this->mve2qt(img, q_img);
	this->display_image(q_img);
	delete q_img;
}

/* Both receives and handles the view pointer that SceneManager emits */
void RegioningPlugin::receive_view_pointer(mve::View::Ptr view_pointer) {
	if (view_pointer != NULL) {
		this->current_view_pointer = view_pointer;
		this->current_image_pointer = view_pointer->get_byte_image("undistorted");
	}
	this->transform_view_pointer(view_pointer);
}

/* This function will handle a view pointer and make it usable for Qt */
void RegioningPlugin::transform_view_pointer(mve::View::Ptr view_pointer) {
	if (view_pointer != NULL) {
		mve::ByteImage::Ptr img = view_pointer->get_byte_image("undistorted");
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
	this->scroll_image2->set_auto_scale(fit);
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
