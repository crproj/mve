/****************************************************************************
** Meta object code from reading C++ file 'addin_rephotographer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_addins/addin_rephotographer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addin_rephotographer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddinRephotographer[] = {

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
      21,   20,   20,   20, 0x09,
      39,   34,   20,   20, 0x09,
      71,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AddinRephotographer[] = {
    "AddinRephotographer\0\0on_rephoto()\0"
    "view\0on_rephoto_view(mve::View::Ptr)\0"
    "on_rephoto_all()\0"
};

void AddinRephotographer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddinRephotographer *_t = static_cast<AddinRephotographer *>(_o);
        switch (_id) {
        case 0: _t->on_rephoto(); break;
        case 1: _t->on_rephoto_view((*reinterpret_cast< mve::View::Ptr(*)>(_a[1]))); break;
        case 2: _t->on_rephoto_all(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddinRephotographer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddinRephotographer::staticMetaObject = {
    { &AddinBase::staticMetaObject, qt_meta_stringdata_AddinRephotographer,
      qt_meta_data_AddinRephotographer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddinRephotographer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddinRephotographer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddinRephotographer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddinRephotographer))
        return static_cast<void*>(const_cast< AddinRephotographer*>(this));
    return AddinBase::qt_metacast(_clname);
}

int AddinRephotographer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AddinBase::qt_metacall(_c, _id, _a);
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
