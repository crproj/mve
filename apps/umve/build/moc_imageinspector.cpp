/****************************************************************************
** Meta object code from reading C++ file 'imageinspector.h'
**
** Created: Wed Jan 21 14:07:57 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../viewinspect/imageinspector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageinspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageInspectorWidget[] = {

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
      32,   22,   21,   21, 0x08,
      77,   22,   21,   21, 0x08,
     123,   22,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImageInspectorWidget[] = {
    "ImageInspectorWidget\0\0x,y,event\0"
    "on_large_image_clicked(int,int,QMouseEvent*)\0"
    "on_medium_image_clicked(int,int,QMouseEvent*)\0"
    "on_small_image_clicked(int,int,QMouseEvent*)\0"
};

void ImageInspectorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageInspectorWidget *_t = static_cast<ImageInspectorWidget *>(_o);
        switch (_id) {
        case 0: _t->on_large_image_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 1: _t->on_medium_image_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 2: _t->on_small_image_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImageInspectorWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageInspectorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageInspectorWidget,
      qt_meta_data_ImageInspectorWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageInspectorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageInspectorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageInspectorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageInspectorWidget))
        return static_cast<void*>(const_cast< ImageInspectorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageInspectorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
