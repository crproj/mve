/****************************************************************************
** Meta object code from reading C++ file 'addin_manager.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_inspect/addin_manager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addin_manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddinManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x09,
      35,   13,   13,   13, 0x09,
      65,   55,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AddinManager[] = {
    "AddinManager\0\0on_set_clear_color()\0"
    "apply_clear_color()\0name,mesh\0"
    "on_mesh_generated(std::string,mve::TriangleMesh::Ptr)\0"
};

void AddinManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddinManager *_t = static_cast<AddinManager *>(_o);
        switch (_id) {
        case 0: _t->on_set_clear_color(); break;
        case 1: _t->apply_clear_color(); break;
        case 2: _t->on_mesh_generated((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< mve::TriangleMesh::Ptr(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddinManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddinManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AddinManager,
      qt_meta_data_AddinManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddinManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddinManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddinManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddinManager))
        return static_cast<void*>(const_cast< AddinManager*>(this));
    if (!strcmp(_clname, "ogl::CameraTrackballContext"))
        return static_cast< ogl::CameraTrackballContext*>(const_cast< AddinManager*>(this));
    return QWidget::qt_metacast(_clname);
}

int AddinManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
