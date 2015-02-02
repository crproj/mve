/****************************************************************************
** Meta object code from reading C++ file 'batchoperations.h'
**
** Created: Wed Jan 21 14:07:57 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../batchoperations.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'batchoperations.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BatchOperations[] = {

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
      17,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BatchOperations[] = {
    "BatchOperations\0\0on_close_clicked()\0"
};

void BatchOperations::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BatchOperations *_t = static_cast<BatchOperations *>(_o);
        switch (_id) {
        case 0: _t->on_close_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BatchOperations::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BatchOperations::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BatchOperations,
      qt_meta_data_BatchOperations, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BatchOperations::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BatchOperations::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BatchOperations::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BatchOperations))
        return static_cast<void*>(const_cast< BatchOperations*>(this));
    return QDialog::qt_metacast(_clname);
}

int BatchOperations::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_BatchDelete[] = {

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
      13,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BatchDelete[] = {
    "BatchDelete\0\0on_batchdel_exec()\0"
};

void BatchDelete::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BatchDelete *_t = static_cast<BatchDelete *>(_o);
        switch (_id) {
        case 0: _t->on_batchdel_exec(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BatchDelete::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BatchDelete::staticMetaObject = {
    { &BatchOperations::staticMetaObject, qt_meta_stringdata_BatchDelete,
      qt_meta_data_BatchDelete, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BatchDelete::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BatchDelete::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BatchDelete::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BatchDelete))
        return static_cast<void*>(const_cast< BatchDelete*>(this));
    return BatchOperations::qt_metacast(_clname);
}

int BatchDelete::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BatchOperations::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_BatchExport[] = {

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
      13,   12,   12,   12, 0x08,
      30,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BatchExport[] = {
    "BatchExport\0\0on_export_exec()\0"
    "on_dirselect()\0"
};

void BatchExport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BatchExport *_t = static_cast<BatchExport *>(_o);
        switch (_id) {
        case 0: _t->on_export_exec(); break;
        case 1: _t->on_dirselect(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BatchExport::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BatchExport::staticMetaObject = {
    { &BatchOperations::staticMetaObject, qt_meta_stringdata_BatchExport,
      qt_meta_data_BatchExport, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BatchExport::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BatchExport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BatchExport::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BatchExport))
        return static_cast<void*>(const_cast< BatchExport*>(this));
    return BatchOperations::qt_metacast(_clname);
}

int BatchExport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BatchOperations::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_BatchImportImages[] = {

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
      19,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BatchImportImages[] = {
    "BatchImportImages\0\0on_import_images()\0"
};

void BatchImportImages::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BatchImportImages *_t = static_cast<BatchImportImages *>(_o);
        switch (_id) {
        case 0: _t->on_import_images(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BatchImportImages::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BatchImportImages::staticMetaObject = {
    { &BatchOperations::staticMetaObject, qt_meta_stringdata_BatchImportImages,
      qt_meta_data_BatchImportImages, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BatchImportImages::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BatchImportImages::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BatchImportImages::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BatchImportImages))
        return static_cast<void*>(const_cast< BatchImportImages*>(this));
    return BatchOperations::qt_metacast(_clname);
}

int BatchImportImages::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BatchOperations::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_BatchGenerateThumbs[] = {

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
      21,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BatchGenerateThumbs[] = {
    "BatchGenerateThumbs\0\0on_generate()\0"
};

void BatchGenerateThumbs::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BatchGenerateThumbs *_t = static_cast<BatchGenerateThumbs *>(_o);
        switch (_id) {
        case 0: _t->on_generate(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BatchGenerateThumbs::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BatchGenerateThumbs::staticMetaObject = {
    { &BatchOperations::staticMetaObject, qt_meta_stringdata_BatchGenerateThumbs,
      qt_meta_data_BatchGenerateThumbs, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BatchGenerateThumbs::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BatchGenerateThumbs::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BatchGenerateThumbs::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BatchGenerateThumbs))
        return static_cast<void*>(const_cast< BatchGenerateThumbs*>(this));
    return BatchOperations::qt_metacast(_clname);
}

int BatchGenerateThumbs::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BatchOperations::qt_metacall(_c, _id, _a);
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
