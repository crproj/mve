/****************************************************************************
** Meta object code from reading C++ file 'jobqueue.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jobqueue.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jobqueue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JobQueue[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x09,
      27,   22,    9,    9, 0x09,
      63,    9,    9,    9, 0x09,
      82,   78,    9,    9, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_JobQueue[] = {
    "JobQueue\0\0on_update()\0item\0"
    "on_item_activated(QListWidgetItem*)\0"
    "add_fake_job()\0job\0update_job(JobQueueEntry&)\0"
};

void JobQueue::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        JobQueue *_t = static_cast<JobQueue *>(_o);
        switch (_id) {
        case 0: _t->on_update(); break;
        case 1: _t->on_item_activated((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->add_fake_job(); break;
        case 3: _t->update_job((*reinterpret_cast< JobQueueEntry(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData JobQueue::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject JobQueue::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_JobQueue,
      qt_meta_data_JobQueue, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JobQueue::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JobQueue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JobQueue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JobQueue))
        return static_cast<void*>(const_cast< JobQueue*>(this));
    return QWidget::qt_metacast(_clname);
}

int JobQueue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
