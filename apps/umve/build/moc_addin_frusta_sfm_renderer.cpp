/****************************************************************************
** Meta object code from reading C++ file 'addin_frusta_sfm_renderer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene_addins/addin_frusta_sfm_renderer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addin_frusta_sfm_renderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddinFrustaSfmRenderer[] = {

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
      24,   23,   23,   23, 0x09,
      48,   23,   23,   23, 0x09,
      73,   23,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AddinFrustaSfmRenderer[] = {
    "AddinFrustaSfmRenderer\0\0reset_frusta_renderer()\0"
    "create_frusta_renderer()\0paint_impl()\0"
};

void AddinFrustaSfmRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddinFrustaSfmRenderer *_t = static_cast<AddinFrustaSfmRenderer *>(_o);
        switch (_id) {
        case 0: _t->reset_frusta_renderer(); break;
        case 1: _t->create_frusta_renderer(); break;
        case 2: _t->paint_impl(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AddinFrustaSfmRenderer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddinFrustaSfmRenderer::staticMetaObject = {
    { &AddinBase::staticMetaObject, qt_meta_stringdata_AddinFrustaSfmRenderer,
      qt_meta_data_AddinFrustaSfmRenderer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddinFrustaSfmRenderer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddinFrustaSfmRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddinFrustaSfmRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddinFrustaSfmRenderer))
        return static_cast<void*>(const_cast< AddinFrustaSfmRenderer*>(this));
    return AddinBase::qt_metacast(_clname);
}

int AddinFrustaSfmRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
