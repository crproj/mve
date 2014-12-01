/****************************************************************************
** Meta object code from reading C++ file 'sfm_controls.h'
**
** Created: Mon Dec 1 13:32:19 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sfm_reconstruct/sfm_controls.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sfm_controls.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SfmControls[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x09,
      34,   12,   12,   12, 0x09,
      63,   12,   12,   12, 0x09,
      88,   12,   12,   12, 0x09,
     108,   12,   12,   12, 0x09,
     129,   12,   12,   12, 0x09,
     151,   12,   12,   12, 0x09,
     171,   12,   12,   12, 0x09,
     191,   12,   12,   12, 0x09,
     212,   12,   12,   12, 0x09,
     235,   12,   12,   12, 0x09,
     258,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SfmControls[] = {
    "SfmControls\0\0initialize_options()\0"
    "create_sfm_points_renderer()\0"
    "update_frusta_renderer()\0apply_clear_color()\0"
    "on_set_clear_color()\0on_matching_compute()\0"
    "on_prebundle_load()\0on_prebundle_save()\0"
    "on_recon_init_pair()\0on_recon_next_camera()\0"
    "on_recon_all_cameras()\0on_apply_to_scene()\0"
};

void SfmControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SfmControls *_t = static_cast<SfmControls *>(_o);
        switch (_id) {
        case 0: _t->initialize_options(); break;
        case 1: _t->create_sfm_points_renderer(); break;
        case 2: _t->update_frusta_renderer(); break;
        case 3: _t->apply_clear_color(); break;
        case 4: _t->on_set_clear_color(); break;
        case 5: _t->on_matching_compute(); break;
        case 6: _t->on_prebundle_load(); break;
        case 7: _t->on_prebundle_save(); break;
        case 8: _t->on_recon_init_pair(); break;
        case 9: _t->on_recon_next_camera(); break;
        case 10: _t->on_recon_all_cameras(); break;
        case 11: _t->on_apply_to_scene(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SfmControls::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SfmControls::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SfmControls,
      qt_meta_data_SfmControls, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SfmControls::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SfmControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SfmControls::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SfmControls))
        return static_cast<void*>(const_cast< SfmControls*>(this));
    if (!strcmp(_clname, "ogl::CameraTrackballContext"))
        return static_cast< ogl::CameraTrackballContext*>(const_cast< SfmControls*>(this));
    return QWidget::qt_metacast(_clname);
}

int SfmControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
