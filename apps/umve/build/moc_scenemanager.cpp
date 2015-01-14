/****************************************************************************
** Meta object code from reading C++ file 'scenemanager.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scenemanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scenemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SceneManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x05,
      57,   52,   13,   13, 0x05,
      93,   87,   13,   13, 0x05,
     129,   13,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SceneManager[] = {
    "SceneManager\0\0scene\0scene_selected(mve::Scene::Ptr)\0"
    "view\0view_selected(mve::View::Ptr)\0"
    "image\0image_selected(mve::ImageBase::Ptr)\0"
    "scene_bundle_changed()\0"
};

void SceneManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SceneManager *_t = static_cast<SceneManager *>(_o);
        switch (_id) {
        case 0: _t->scene_selected((*reinterpret_cast< mve::Scene::Ptr(*)>(_a[1]))); break;
        case 1: _t->view_selected((*reinterpret_cast< mve::View::Ptr(*)>(_a[1]))); break;
        case 2: _t->image_selected((*reinterpret_cast< mve::ImageBase::Ptr(*)>(_a[1]))); break;
        case 3: _t->scene_bundle_changed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SceneManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SceneManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SceneManager,
      qt_meta_data_SceneManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SceneManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SceneManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SceneManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneManager))
        return static_cast<void*>(const_cast< SceneManager*>(this));
    return QObject::qt_metacast(_clname);
}

int SceneManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SceneManager::scene_selected(mve::Scene::Ptr _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SceneManager::view_selected(mve::View::Ptr _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SceneManager::image_selected(mve::ImageBase::Ptr _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SceneManager::scene_bundle_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
