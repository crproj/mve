/****************************************************************************
** Meta object code from reading C++ file 'regioning_plugin.h'
**
** Created: Mon Nov 24 14:12:00 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../regioning_plugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'regioning_plugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RegioningPlugin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      36,   16,   16,   16, 0x08,
      73,   16,   16,   16, 0x08,
      86,   16,   16,   16, 0x08,
     100,   16,   16,   16, 0x08,
     117,   16,   16,   16, 0x08,
     146,  136,   16,   16, 0x08,
     185,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RegioningPlugin[] = {
    "RegioningPlugin\0\0handle_save_view()\0"
    "receive_view_pointer(mve::View::Ptr)\0"
    "on_zoom_in()\0on_zoom_out()\0on_normal_size()\0"
    "on_fit_to_window()\0x,y,event\0"
    "on_image_clicked(int,int,QMouseEvent*)\0"
    "on_details_toggled()\0"
};

void RegioningPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RegioningPlugin *_t = static_cast<RegioningPlugin *>(_o);
        switch (_id) {
        case 0: _t->handle_save_view(); break;
        case 1: _t->receive_view_pointer((*reinterpret_cast< mve::View::Ptr(*)>(_a[1]))); break;
        case 2: _t->on_zoom_in(); break;
        case 3: _t->on_zoom_out(); break;
        case 4: _t->on_normal_size(); break;
        case 5: _t->on_fit_to_window(); break;
        case 6: _t->on_image_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 7: _t->on_details_toggled(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RegioningPlugin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RegioningPlugin::staticMetaObject = {
    { &MainWindowTab::staticMetaObject, qt_meta_stringdata_RegioningPlugin,
      qt_meta_data_RegioningPlugin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RegioningPlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RegioningPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RegioningPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RegioningPlugin))
        return static_cast<void*>(const_cast< RegioningPlugin*>(this));
    if (!strcmp(_clname, MainWindowTab_iid))
        return static_cast< MainWindowTab*>(const_cast< RegioningPlugin*>(this));
    return MainWindowTab::qt_metacast(_clname);
}

int RegioningPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MainWindowTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE