/****************************************************************************
** Meta object code from reading C++ file 'imageoperations.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../viewinspect/imageoperations.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageoperations.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageOperationsWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,
      55,   50,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      88,   22,   22,   22, 0x08,
     103,   22,   22,   22, 0x08,
     118,   22,   22,   22, 0x08,
     144,  139,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImageOperationsWidget[] = {
    "ImageOperationsWidget\0\0"
    "signal_reload_embeddings()\0name\0"
    "signal_select_embedding(QString)\0"
    "exec_dmrecon()\0exec_dmclean()\0"
    "exec_dmrecon_batch()\0view\0"
    "on_view_selected(mve::View::Ptr)\0"
};

void ImageOperationsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageOperationsWidget *_t = static_cast<ImageOperationsWidget *>(_o);
        switch (_id) {
        case 0: _t->signal_reload_embeddings(); break;
        case 1: _t->signal_select_embedding((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->exec_dmrecon(); break;
        case 3: _t->exec_dmclean(); break;
        case 4: _t->exec_dmrecon_batch(); break;
        case 5: _t->on_view_selected((*reinterpret_cast< mve::View::Ptr(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImageOperationsWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageOperationsWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageOperationsWidget,
      qt_meta_data_ImageOperationsWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageOperationsWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageOperationsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageOperationsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageOperationsWidget))
        return static_cast<void*>(const_cast< ImageOperationsWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageOperationsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ImageOperationsWidget::signal_reload_embeddings()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ImageOperationsWidget::signal_select_embedding(QString const & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
