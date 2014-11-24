/****************************************************************************
** Meta object code from reading C++ file 'viewinspect.h'
**
** Created: Thu Nov 6 12:07:15 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../viewinspect/viewinspect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewinspect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ViewInspect[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      23,   12,   12,   12, 0x08,
      36,   12,   12,   12, 0x08,
      50,   12,   12,   12, 0x08,
      67,   12,   12,   12, 0x08,
      86,   12,   12,   12, 0x08,
     112,  107,   12,   12, 0x08,
     143,   12,   12,   12, 0x08,
     159,   12,   12,   12, 0x08,
     177,   12,   12,   12, 0x08,
     197,   12,   12,   12, 0x08,
     216,   12,   12,   12, 0x08,
     231,   12,   12,   12, 0x08,
     248,   12,   12,   12, 0x08,
     281,  271,   12,   12, 0x08,
     320,   12,   12,   12, 0x08,
     352,  346,   12,   12, 0x08,
     392,  387,   12,   12, 0x08,
     425,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ViewInspect[] = {
    "ViewInspect\0\0on_open()\0on_zoom_in()\0"
    "on_zoom_out()\0on_normal_size()\0"
    "on_fit_to_window()\0on_details_toggled()\0"
    "name\0on_embedding_selected(QString)\0"
    "on_ply_export()\0on_image_export()\0"
    "on_copy_embedding()\0on_del_embedding()\0"
    "on_save_view()\0on_view_reload()\0"
    "on_reload_embeddings()\0x,y,event\0"
    "on_image_clicked(int,int,QMouseEvent*)\0"
    "on_tone_mapping_changed()\0scene\0"
    "on_scene_selected(mve::Scene::Ptr)\0"
    "view\0on_view_selected(mve::View::Ptr)\0"
    "on_tab_activated()\0"
};

void ViewInspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ViewInspect *_t = static_cast<ViewInspect *>(_o);
        switch (_id) {
        case 0: _t->on_open(); break;
        case 1: _t->on_zoom_in(); break;
        case 2: _t->on_zoom_out(); break;
        case 3: _t->on_normal_size(); break;
        case 4: _t->on_fit_to_window(); break;
        case 5: _t->on_details_toggled(); break;
        case 6: _t->on_embedding_selected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_ply_export(); break;
        case 8: _t->on_image_export(); break;
        case 9: _t->on_copy_embedding(); break;
        case 10: _t->on_del_embedding(); break;
        case 11: _t->on_save_view(); break;
        case 12: _t->on_view_reload(); break;
        case 13: _t->on_reload_embeddings(); break;
        case 14: _t->on_image_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 15: _t->on_tone_mapping_changed(); break;
        case 16: _t->on_scene_selected((*reinterpret_cast< mve::Scene::Ptr(*)>(_a[1]))); break;
        case 17: _t->on_view_selected((*reinterpret_cast< mve::View::Ptr(*)>(_a[1]))); break;
        case 18: _t->on_tab_activated(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ViewInspect::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ViewInspect::staticMetaObject = {
    { &MainWindowTab::staticMetaObject, qt_meta_stringdata_ViewInspect,
      qt_meta_data_ViewInspect, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ViewInspect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ViewInspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ViewInspect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewInspect))
        return static_cast<void*>(const_cast< ViewInspect*>(this));
    return MainWindowTab::qt_metacast(_clname);
}

int ViewInspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MainWindowTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
