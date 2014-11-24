/****************************************************************************
** Meta object code from reading C++ file 'addin_base.h'
**
** Created: Thu Nov 6 12:07:15 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_addins/addin_base.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addin_base.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddinBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   10,   10,   10, 0x09,
      82,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AddinBase[] = {
    "AddinBase\0\0name,mesh\0"
    "mesh_generated(std::string,mve::TriangleMesh::Ptr)\0"
    "repaint()\0request_context()\0"
};

void AddinBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddinBase *_t = static_cast<AddinBase *>(_o);
        switch (_id) {
        case 0: _t->mesh_generated((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< mve::TriangleMesh::Ptr(*)>(_a[2]))); break;
        case 1: _t->repaint(); break;
        case 2: _t->request_context(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddinBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddinBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AddinBase,
      qt_meta_data_AddinBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddinBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddinBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddinBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddinBase))
        return static_cast<void*>(const_cast< AddinBase*>(this));
    if (!strcmp(_clname, "ogl::Context"))
        return static_cast< ogl::Context*>(const_cast< AddinBase*>(this));
    return QObject::qt_metacast(_clname);
}

int AddinBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AddinBase::mesh_generated(std::string const & _t1, mve::TriangleMesh::Ptr _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
