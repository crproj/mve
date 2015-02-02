/****************************************************************************
** Meta object code from reading C++ file 'tonemapping.h'
**
** Created: Wed Jan 21 14:07:57 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../viewinspect/tonemapping.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tonemapping.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ToneMappingHistogram[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ToneMappingHistogram[] = {
    "ToneMappingHistogram\0\0start,end\0"
    "mapping_area_changed(float,float)\0"
    "on_timer_expired()\0"
};

void ToneMappingHistogram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ToneMappingHistogram *_t = static_cast<ToneMappingHistogram *>(_o);
        switch (_id) {
        case 0: _t->mapping_area_changed((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->on_timer_expired(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ToneMappingHistogram::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ToneMappingHistogram::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ToneMappingHistogram,
      qt_meta_data_ToneMappingHistogram, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ToneMappingHistogram::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ToneMappingHistogram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ToneMappingHistogram::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToneMappingHistogram))
        return static_cast<void*>(const_cast< ToneMappingHistogram*>(this));
    return QWidget::qt_metacast(_clname);
}

int ToneMappingHistogram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ToneMappingHistogram::mapping_area_changed(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ToneMapping[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   12,   12,   12, 0x08,
      61,   12,   12,   12, 0x08,
     100,   90,   12,   12, 0x08,
     142,  137,   12,   12, 0x08,
     167,   12,   12,   12, 0x08,
     192,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ToneMapping[] = {
    "ToneMapping\0\0tone_mapping_changed()\0"
    "on_gamma_value_changed()\0"
    "on_highlight_value_changed()\0start,end\0"
    "on_mapping_area_changed(float,float)\0"
    "mask\0on_channels_changed(int)\0"
    "on_update_tone_mapping()\0"
    "on_ignore_zeroes_changed()\0"
};

void ToneMapping::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ToneMapping *_t = static_cast<ToneMapping *>(_o);
        switch (_id) {
        case 0: _t->tone_mapping_changed(); break;
        case 1: _t->on_gamma_value_changed(); break;
        case 2: _t->on_highlight_value_changed(); break;
        case 3: _t->on_mapping_area_changed((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: _t->on_channels_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_update_tone_mapping(); break;
        case 6: _t->on_ignore_zeroes_changed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ToneMapping::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ToneMapping::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ToneMapping,
      qt_meta_data_ToneMapping, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ToneMapping::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ToneMapping::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ToneMapping::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToneMapping))
        return static_cast<void*>(const_cast< ToneMapping*>(this));
    return QWidget::qt_metacast(_clname);
}

int ToneMapping::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ToneMapping::tone_mapping_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
