/****************************************************************************
** Meta object code from reading C++ file 'addin_sphere_creator.h'
**
** Created: Wed Jan 21 14:07:58 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_addins/addin_sphere_creator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addin_sphere_creator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddinSphereCreator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddinSphereCreator[] = {
    "AddinSphereCreator\0\0on_create_clicked()\0"
};

void AddinSphereCreator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddinSphereCreator *_t = static_cast<AddinSphereCreator *>(_o);
        switch (_id) {
        case 0: _t->on_create_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AddinSphereCreator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddinSphereCreator::staticMetaObject = {
    { &AddinBase::staticMetaObject, qt_meta_stringdata_AddinSphereCreator,
      qt_meta_data_AddinSphereCreator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddinSphereCreator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddinSphereCreator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddinSphereCreator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddinSphereCreator))
        return static_cast<void*>(const_cast< AddinSphereCreator*>(this));
    return AddinBase::qt_metacast(_clname);
}

int AddinSphereCreator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AddinBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
