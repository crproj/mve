/****************************************************************************
** Meta object code from reading C++ file 'addin_dm_triangulate.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_addins/addin_dm_triangulate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addin_dm_triangulate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddinDMTriangulate[] = {

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
      20,   19,   19,   19, 0x08,
      50,   45,   19,   19, 0x08,
      80,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddinDMTriangulate[] = {
    "AddinDMTriangulate\0\0on_triangulate_clicked()\0"
    "name\0on_select_colorimage(QString)\0"
    "on_view_selected()\0"
};

void AddinDMTriangulate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddinDMTriangulate *_t = static_cast<AddinDMTriangulate *>(_o);
        switch (_id) {
        case 0: _t->on_triangulate_clicked(); break;
        case 1: _t->on_select_colorimage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_view_selected(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddinDMTriangulate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddinDMTriangulate::staticMetaObject = {
    { &AddinBase::staticMetaObject, qt_meta_stringdata_AddinDMTriangulate,
      qt_meta_data_AddinDMTriangulate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddinDMTriangulate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddinDMTriangulate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddinDMTriangulate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddinDMTriangulate))
        return static_cast<void*>(const_cast< AddinDMTriangulate*>(this));
    return AddinBase::qt_metacast(_clname);
}

int AddinDMTriangulate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
