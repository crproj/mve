/****************************************************************************
** Meta object code from reading C++ file 'addin_offscreen_renderer.h'
**
** Created: Thu Nov 6 12:07:15 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_addins/addin_offscreen_renderer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addin_offscreen_renderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddinOffscreenRenderer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      38,   23,   23,   23, 0x08,
      64,   59,   23,   23, 0x08,
      87,   23,   23,   23, 0x28,
     106,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddinOffscreenRenderer[] = {
    "AddinOffscreenRenderer\0\0on_snapshot()\0"
    "on_render_sequence()\0save\0"
    "on_play_sequence(bool)\0on_play_sequence()\0"
    "on_display_sequence()\0"
};

void AddinOffscreenRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddinOffscreenRenderer *_t = static_cast<AddinOffscreenRenderer *>(_o);
        switch (_id) {
        case 0: _t->on_snapshot(); break;
        case 1: _t->on_render_sequence(); break;
        case 2: _t->on_play_sequence((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_play_sequence(); break;
        case 4: _t->on_display_sequence(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddinOffscreenRenderer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddinOffscreenRenderer::staticMetaObject = {
    { &AddinBase::staticMetaObject, qt_meta_stringdata_AddinOffscreenRenderer,
      qt_meta_data_AddinOffscreenRenderer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddinOffscreenRenderer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddinOffscreenRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddinOffscreenRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddinOffscreenRenderer))
        return static_cast<void*>(const_cast< AddinOffscreenRenderer*>(this));
    return AddinBase::qt_metacast(_clname);
}

int AddinOffscreenRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AddinBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
