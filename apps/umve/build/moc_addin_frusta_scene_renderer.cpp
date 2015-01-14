/****************************************************************************
** Meta object code from reading C++ file 'addin_frusta_scene_renderer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_addins/addin_frusta_scene_renderer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addin_frusta_scene_renderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddinFrustaSceneRenderer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x09,
      51,   25,   25,   25, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AddinFrustaSceneRenderer[] = {
    "AddinFrustaSceneRenderer\0\0"
    "reset_viewdir_renderer()\0"
    "reset_frusta_renderer()\0"
};

void AddinFrustaSceneRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddinFrustaSceneRenderer *_t = static_cast<AddinFrustaSceneRenderer *>(_o);
        switch (_id) {
        case 0: _t->reset_viewdir_renderer(); break;
        case 1: _t->reset_frusta_renderer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AddinFrustaSceneRenderer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddinFrustaSceneRenderer::staticMetaObject = {
    { &AddinBase::staticMetaObject, qt_meta_stringdata_AddinFrustaSceneRenderer,
      qt_meta_data_AddinFrustaSceneRenderer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddinFrustaSceneRenderer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddinFrustaSceneRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddinFrustaSceneRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddinFrustaSceneRenderer))
        return static_cast<void*>(const_cast< AddinFrustaSceneRenderer*>(this));
    return AddinBase::qt_metacast(_clname);
}

int AddinFrustaSceneRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AddinBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
