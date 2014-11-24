/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Nov 24 14:41:44 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      27,   11,   11,   11, 0x08,
      45,   11,   11,   11, 0x08,
      61,   11,   11,   11, 0x08,
      78,   11,   11,   11, 0x08,
      97,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     127,   11,   11,   11, 0x08,
     146,   11,   11,   11, 0x08,
     165,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     229,  222,   11,   11, 0x08,
     255,  249,   11,   11, 0x08,
     280,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_new_scene()\0on_reload_scene()\0"
    "on_save_scene()\0on_close_scene()\0"
    "on_refresh_scene()\0on_about()\0"
    "on_import_images()\0on_update_memory()\0"
    "on_cache_cleanup()\0on_recon_export()\0"
    "on_batch_delete()\0on_generate_thumbs()\0"
    "tab_id\0on_switch_tabs(int)\0event\0"
    "closeEvent(QCloseEvent*)\0"
    "raise_open_scene_dialog()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_new_scene(); break;
        case 1: _t->on_reload_scene(); break;
        case 2: _t->on_save_scene(); break;
        case 3: _t->on_close_scene(); break;
        case 4: _t->on_refresh_scene(); break;
        case 5: _t->on_about(); break;
        case 6: _t->on_import_images(); break;
        case 7: _t->on_update_memory(); break;
        case 8: _t->on_cache_cleanup(); break;
        case 9: _t->on_recon_export(); break;
        case 10: _t->on_batch_delete(); break;
        case 11: _t->on_generate_thumbs(); break;
        case 12: _t->on_switch_tabs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 14: _t->raise_open_scene_dialog(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
