/****************************************************************************
** Meta object code from reading C++ file 'ClickButton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Classes/ClickButton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClickButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClickButton_t {
    QByteArrayData data[10];
    char stringdata[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClickButton_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClickButton_t qt_meta_stringdata_ClickButton = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ClickButton"
QT_MOC_LITERAL(1, 12, 15), // "mousePressEvent"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 42, 1), // "e"
QT_MOC_LITERAL(5, 44, 9), // "DelAction"
QT_MOC_LITERAL(6, 54, 9), // "DddAction"
QT_MOC_LITERAL(7, 64, 7), // "DelLine"
QT_MOC_LITERAL(8, 72, 8), // "DelFrame"
QT_MOC_LITERAL(9, 81, 7) // "FreeBox"

    },
    "ClickButton\0mousePressEvent\0\0QMouseEvent*\0"
    "e\0DelAction\0DddAction\0DelLine\0DelFrame\0"
    "FreeBox"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClickButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,
       8,    0,   50,    2, 0x08 /* Private */,
       9,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ClickButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClickButton *_t = static_cast<ClickButton *>(_o);
        switch (_id) {
        case 0: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->DelAction(); break;
        case 2: _t->DddAction(); break;
        case 3: _t->DelLine(); break;
        case 4: _t->DelFrame(); break;
        case 5: _t->FreeBox(); break;
        default: ;
        }
    }
}

const QMetaObject ClickButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_ClickButton.data,
      qt_meta_data_ClickButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ClickButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClickButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ClickButton.stringdata))
        return static_cast<void*>(const_cast< ClickButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int ClickButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
