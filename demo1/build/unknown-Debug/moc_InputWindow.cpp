/****************************************************************************
** Meta object code from reading C++ file 'InputWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../InputWindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InputWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSInputWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSInputWindowENDCLASS = QtMocHelpers::stringData(
    "InputWindow",
    "recordSaved",
    "",
    "Record",
    "record",
    "windowShowed",
    "windowHided",
    "onSaveClicked",
    "onClearClicked",
    "onMoodChanged",
    "index"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSInputWindowENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[12];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[7];
    char stringdata5[13];
    char stringdata6[12];
    char stringdata7[14];
    char stringdata8[15];
    char stringdata9[14];
    char stringdata10[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSInputWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSInputWindowENDCLASS_t qt_meta_stringdata_CLASSInputWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "InputWindow"
        QT_MOC_LITERAL(12, 11),  // "recordSaved"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 6),  // "Record"
        QT_MOC_LITERAL(32, 6),  // "record"
        QT_MOC_LITERAL(39, 12),  // "windowShowed"
        QT_MOC_LITERAL(52, 11),  // "windowHided"
        QT_MOC_LITERAL(64, 13),  // "onSaveClicked"
        QT_MOC_LITERAL(78, 14),  // "onClearClicked"
        QT_MOC_LITERAL(93, 13),  // "onMoodChanged"
        QT_MOC_LITERAL(107, 5)   // "index"
    },
    "InputWindow",
    "recordSaved",
    "",
    "Record",
    "record",
    "windowShowed",
    "windowHided",
    "onSaveClicked",
    "onClearClicked",
    "onMoodChanged",
    "index"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInputWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       5,    0,   53,    2, 0x06,    3 /* Public */,
       6,    0,   54,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   55,    2, 0x08,    5 /* Private */,
       8,    0,   56,    2, 0x08,    6 /* Private */,
       9,    1,   57,    2, 0x08,    7 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

Q_CONSTINIT const QMetaObject InputWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSInputWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSInputWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSInputWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<InputWindow, std::true_type>,
        // method 'recordSaved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Record &, std::false_type>,
        // method 'windowShowed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'windowHided'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClearClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMoodChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void InputWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InputWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->recordSaved((*reinterpret_cast< std::add_pointer_t<Record>>(_a[1]))); break;
        case 1: _t->windowShowed(); break;
        case 2: _t->windowHided(); break;
        case 3: _t->onSaveClicked(); break;
        case 4: _t->onClearClicked(); break;
        case 5: _t->onMoodChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InputWindow::*)(const Record & );
            if (_t _q_method = &InputWindow::recordSaved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InputWindow::*)();
            if (_t _q_method = &InputWindow::windowShowed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (InputWindow::*)();
            if (_t _q_method = &InputWindow::windowHided; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *InputWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSInputWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int InputWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void InputWindow::recordSaved(const Record & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InputWindow::windowShowed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void InputWindow::windowHided()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
