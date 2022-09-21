/****************************************************************************
** Meta object code from reading C++ file 'realtime.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Include/realtime.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'realtime.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MeshWidget_t {
    const uint offsetsAndSize[38];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MeshWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MeshWidget_t qt_meta_stringdata_MeshWidget = {
    {
QT_MOC_LITERAL(0, 10), // "MeshWidget"
QT_MOC_LITERAL(11, 13), // "_signalUpdate"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 20), // "_signalMouseMoveEdit"
QT_MOC_LITERAL(47, 12), // "QMouseEvent*"
QT_MOC_LITERAL(60, 16), // "_signalMouseMove"
QT_MOC_LITERAL(77, 19), // "_signalMouseRelease"
QT_MOC_LITERAL(97, 20), // "_signalEditSceneLeft"
QT_MOC_LITERAL(118, 3), // "Ray"
QT_MOC_LITERAL(122, 21), // "_signalEditSceneRight"
QT_MOC_LITERAL(144, 15), // "mousePressEvent"
QT_MOC_LITERAL(160, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(178, 21), // "mouseDoubleClickEvent"
QT_MOC_LITERAL(200, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(215, 10), // "wheelEvent"
QT_MOC_LITERAL(226, 12), // "QWheelEvent*"
QT_MOC_LITERAL(239, 13), // "keyPressEvent"
QT_MOC_LITERAL(253, 10), // "QKeyEvent*"
QT_MOC_LITERAL(264, 15) // "keyReleaseEvent"

    },
    "MeshWidget\0_signalUpdate\0\0"
    "_signalMouseMoveEdit\0QMouseEvent*\0"
    "_signalMouseMove\0_signalMouseRelease\0"
    "_signalEditSceneLeft\0Ray\0_signalEditSceneRight\0"
    "mousePressEvent\0mouseReleaseEvent\0"
    "mouseDoubleClickEvent\0mouseMoveEvent\0"
    "wheelEvent\0QWheelEvent*\0keyPressEvent\0"
    "QKeyEvent*\0keyReleaseEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MeshWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x06,    1 /* Public */,
       3,    1,   93,    2, 0x06,    2 /* Public */,
       5,    1,   96,    2, 0x06,    4 /* Public */,
       6,    0,   99,    2, 0x06,    6 /* Public */,
       7,    1,  100,    2, 0x06,    7 /* Public */,
       9,    1,  103,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,  106,    2, 0x0a,   11 /* Public */,
      11,    1,  109,    2, 0x0a,   13 /* Public */,
      12,    1,  112,    2, 0x0a,   15 /* Public */,
      13,    1,  115,    2, 0x0a,   17 /* Public */,
      14,    1,  118,    2, 0x0a,   19 /* Public */,
      16,    1,  121,    2, 0x0a,   21 /* Public */,
      18,    1,  124,    2, 0x0a,   23 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 8,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 17,    2,

       0        // eod
};

void MeshWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MeshWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->_signalUpdate(); break;
        case 1: _t->_signalMouseMoveEdit((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 2: _t->_signalMouseMove((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 3: _t->_signalMouseRelease(); break;
        case 4: _t->_signalEditSceneLeft((*reinterpret_cast< std::add_pointer_t<Ray>>(_a[1]))); break;
        case 5: _t->_signalEditSceneRight((*reinterpret_cast< std::add_pointer_t<Ray>>(_a[1]))); break;
        case 6: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 7: _t->mouseReleaseEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 8: _t->mouseDoubleClickEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 9: _t->mouseMoveEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 10: _t->wheelEvent((*reinterpret_cast< std::add_pointer_t<QWheelEvent*>>(_a[1]))); break;
        case 11: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 12: _t->keyReleaseEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MeshWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshWidget::_signalUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MeshWidget::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshWidget::_signalMouseMoveEdit)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MeshWidget::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshWidget::_signalMouseMove)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MeshWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshWidget::_signalMouseRelease)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MeshWidget::*)(const Ray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshWidget::_signalEditSceneLeft)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MeshWidget::*)(const Ray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshWidget::_signalEditSceneRight)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject MeshWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_MeshWidget.offsetsAndSize,
    qt_meta_data_MeshWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MeshWidget_t
, QtPrivate::TypeAndForceComplete<MeshWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Ray &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Ray &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QWheelEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>


>,
    nullptr
} };


const QMetaObject *MeshWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeshWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MeshWidget.stringdata0))
        return static_cast<void*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int MeshWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MeshWidget::_signalUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MeshWidget::_signalMouseMoveEdit(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MeshWidget::_signalMouseMove(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MeshWidget::_signalMouseRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MeshWidget::_signalEditSceneLeft(const Ray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MeshWidget::_signalEditSceneRight(const Ray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
