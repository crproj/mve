#ifndef REGIONING_TAB_HEADER
#define REGIONING_TAB_HEADER

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>
#include <QToolBar>
#include "quadrangle.h"
#include "mainwindowtab.h"
#include "mve/scene.h"
#include "mve/bundle.h"
#include "mve/image.h"

#include "addin_manager.h"
#include "scrollimage.h"

#include "regioning.h"

class RegioningPlugin : public MainWindowTab {
	Q_OBJECT
	#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID MainWindowTab_iid)
	#endif
	Q_INTERFACES(MainWindowTab)
    public:
	RegioningPlugin(QWidget *parent = NULL);
	virtual ~RegioningPlugin();
	virtual QString get_title();
    private:
        QTabWidget* tab_widget;
        AddinManager* addin_manager;
        GLWidget* gl_widget;
	QToolBar *toolbar;
	QLabel *spinbox_region_id_label;
	QAction *save_view;
	QAction *save_all_views;
	QAction *button_apply;
	QAction *button_apply_all;
	QAction *button_apply_to_depth_map;
	QAction *button_apply_to_all_depth_maps;
	QAction *action_zoom_in;
	QAction *action_zoom_out;
	QAction *action_zoom_reset;
	QAction *action_zoom_fit;
	    QAction* action_show_details;
	Quadrangle *q1;
	Quadrangle *q2;

	bool odd;
	
	ScrollImage *scroll_image;
	ScrollImage *scroll_image2;
	void update_actions(void);
	void display_image(QImage *qImg);
	void display_image(QPixmap *pixmap);
	void display_image(mve::ByteImage::ConstPtr img);
	void display_original();
	bool display_result();
	void display_best();
	void mve2qt(mve::ByteImage::ConstPtr src, QImage *dest);
	void transform_view_pointer(mve::View::Ptr);
    void create_actions (QToolBar* toolbar2);
	bool create_debug_images;
	QSpinBox *spinbox_region_id;
	QColorDialog *color_dialog;
	mve::ByteImage::Ptr current_image_pointer;
	mve::View::Ptr current_view_pointer;
	mve::FloatImage::Ptr depth_map_pointer;

    private slots:
	void handle_save_view();
	void receive_view_pointer(mve::View::Ptr);
	void on_zoom_in(void);
	void on_zoom_out(void);
	void on_normal_size(void);
	void on_fit_to_window(void);
	void on_image_clicked(int x, int y, QMouseEvent *event);
    void on_details_toggled (void);

};
#endif /* SKY_KEYING_TAB_HEADER */
