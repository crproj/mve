/****************************************************************************
** Meta object code from reading C++ file 'scene_inspect.h'
**
** Created: Wed Jan 21 14:07:58 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_inspect/scene_inspect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene_inspect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SceneInspect[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      29,   13,   13,   13, 0x08,
      49,   13,   13,   13, 0x08,
      70,   13,   13,   13, 0x08,
      97,   91,   13,   13, 0x08,
     137,  132,   13,   13, 0x08,
     170,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SceneInspect[] = {
    "SceneInspect\0\0on_open_mesh()\0"
    "on_reload_shaders()\0on_details_toggled()\0"
    "on_save_screenshot()\0scene\0"
    "on_scene_selected(mve::Scene::Ptr)\0"
    "view\0on_view_selected(mve::View::Ptr)\0"
    "on_tab_activated()\0"
};

void SceneInspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SceneInspect *_t = static_cast<SceneInspect *>(_o);
        switch (_id) {
        case 0: _t->on_open_mesh(); break;
        case 1: _t->on_reload_shaders(); break;
        case 2: _t->on_details_toggled(); break;
        case 3: _t->on_save_screenshot(); break;
        case 4: _t->on_scene_selected((*reinterpret_cast< mve::Scene::Ptr(*)>(_a[1]))); break;
        case 5: _t->on_view_selected((*reinterpret_cast< mve::View::Ptr(*)>(_a[1]))); break;
        case 6: _t->on_tab_activated(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SceneInspect::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SceneInspect::staticMetaObject = {
    { &MainWindowTab::staticMetaObject, qt_meta_stringdata_SceneInspect,
      qt_meta_data_SceneInspect, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SceneInspect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SceneInspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SceneInspect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneInspect))
        return static_cast<void*>(const_cast< SceneInspect*>(this));
    return MainWindowTab::qt_metacast(_clname);
}

int SceneInspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MainWindowTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
