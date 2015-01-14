/****************************************************************************
** Meta object code from reading C++ file 'mesh_list.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_addins/mesh_list.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mesh_list.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QMeshContextMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      35,   17,   17,   17, 0x08,
      53,   17,   17,   17, 0x08,
      71,   17,   17,   17, 0x08,
      93,   17,   17,   17, 0x08,
     108,   17,   17,   17, 0x08,
     125,   17,   17,   17, 0x08,
     152,   17,   17,   17, 0x08,
     178,   17,   17,   17, 0x08,
     209,   17,   17,   17, 0x08,
     235,   17,   17,   17, 0x08,
     261,   17,   17,   17, 0x08,
     289,  282,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QMeshContextMenu[] = {
    "QMeshContextMenu\0\0on_reload_mesh()\0"
    "on_invert_faces()\0on_delete_faces()\0"
    "on_scale_and_center()\0on_save_mesh()\0"
    "on_rename_mesh()\0on_delete_vertex_normals()\0"
    "on_delete_vertex_colors()\0"
    "on_delete_vertex_confidences()\0"
    "on_colorize_confidences()\0"
    "on_delete_vertex_values()\0"
    "on_colorize_values()\0attrib\0"
    "on_colorize_with_attrib(std::vector<float>)\0"
};

void QMeshContextMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QMeshContextMenu *_t = static_cast<QMeshContextMenu *>(_o);
        switch (_id) {
        case 0: _t->on_reload_mesh(); break;
        case 1: _t->on_invert_faces(); break;
        case 2: _t->on_delete_faces(); break;
        case 3: _t->on_scale_and_center(); break;
        case 4: _t->on_save_mesh(); break;
        case 5: _t->on_rename_mesh(); break;
        case 6: _t->on_delete_vertex_normals(); break;
        case 7: _t->on_delete_vertex_colors(); break;
        case 8: _t->on_delete_vertex_confidences(); break;
        case 9: _t->on_colorize_confidences(); break;
        case 10: _t->on_delete_vertex_values(); break;
        case 11: _t->on_colorize_values(); break;
        case 12: _t->on_colorize_with_attrib((*reinterpret_cast< std::vector<float>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QMeshContextMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QMeshContextMenu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_QMeshContextMenu,
      qt_meta_data_QMeshContextMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QMeshContextMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QMeshContextMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QMeshContextMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QMeshContextMenu))
        return static_cast<void*>(const_cast< QMeshContextMenu*>(this));
    return QMenu::qt_metacast(_clname);
}

int QMeshContextMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
static const uint qt_meta_data_QMeshList[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   27,   10,   10, 0x09,
      68,   27,   10,   10, 0x09,
     102,   10,   10,   10, 0x09,
     118,   10,   10,   10, 0x09,
     135,   10,   10,   10, 0x09,
     152,   10,   10,   10, 0x09,
     171,   10,   10,   10, 0x09,
     194,  190,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QMeshList[] = {
    "QMeshList\0\0signal_redraw()\0item\0"
    "on_item_activated(QListWidgetItem*)\0"
    "on_item_changed(QListWidgetItem*)\0"
    "on_select_all()\0on_select_none()\0"
    "on_select_next()\0on_inv_selection()\0"
    "on_select_toggle()\0pos\0"
    "on_list_context_menu(QPoint)\0"
};

void QMeshList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QMeshList *_t = static_cast<QMeshList *>(_o);
        switch (_id) {
        case 0: _t->signal_redraw(); break;
        case 1: _t->on_item_activated((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->on_item_changed((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->on_select_all(); break;
        case 4: _t->on_select_none(); break;
        case 5: _t->on_select_next(); break;
        case 6: _t->on_inv_selection(); break;
        case 7: _t->on_select_toggle(); break;
        case 8: _t->on_list_context_menu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QMeshList::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QMeshList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QMeshList,
      qt_meta_data_QMeshList, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QMeshList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QMeshList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QMeshList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QMeshList))
        return static_cast<void*>(const_cast< QMeshList*>(this));
    return QWidget::qt_metacast(_clname);
}

int QMeshList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QMeshList::signal_redraw()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
