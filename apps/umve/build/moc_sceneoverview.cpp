/****************************************************************************
** Meta object code from reading C++ file 'sceneoverview.h'
**
** Created: Thu Nov 6 12:07:15 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sceneoverview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sceneoverview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SceneOverview[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x09,
      58,   55,   14,   14, 0x09,
      78,   14,   14,   14, 0x09,
      98,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SceneOverview[] = {
    "SceneOverview\0\0scene\0"
    "on_scene_changed(mve::Scene::Ptr)\0id\0"
    "on_row_changed(int)\0on_filter_changed()\0"
    "on_clear_filter()\0"
};

void SceneOverview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SceneOverview *_t = static_cast<SceneOverview *>(_o);
        switch (_id) {
        case 0: _t->on_scene_changed((*reinterpret_cast< mve::Scene::Ptr(*)>(_a[1]))); break;
        case 1: _t->on_row_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_filter_changed(); break;
        case 3: _t->on_clear_filter(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SceneOverview::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SceneOverview::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SceneOverview,
      qt_meta_data_SceneOverview, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SceneOverview::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SceneOverview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SceneOverview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneOverview))
        return static_cast<void*>(const_cast< SceneOverview*>(this));
    return QWidget::qt_metacast(_clname);
}

int SceneOverview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
