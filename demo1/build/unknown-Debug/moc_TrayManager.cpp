/****************************************************************************
** Meta object code from reading C++ file 'TrayManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TrayManager.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrayManager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSTrayManagerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTrayManagerENDCLASS = QtMocHelpers::stringData(
    "TrayManager",
    "showInputWindowRequested",
    "",
    "showHistoryWindowRequested",
    "showPetRequested",
    "hideAllRequested",
    "backupRequested",
    "restoreRequested",
    "quitRequested",
    "onShowInput",
    "onShowHistory",
    "onShowPet",
    "onHideAll",
    "onBackupData",
    "onRestoreData",
    "onQuit"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTrayManagerENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[12];
    char stringdata1[25];
    char stringdata2[1];
    char stringdata3[27];
    char stringdata4[17];
    char stringdata5[17];
    char stringdata6[16];
    char stringdata7[17];
    char stringdata8[14];
    char stringdata9[12];
    char stringdata10[14];
    char stringdata11[10];
    char stringdata12[10];
    char stringdata13[13];
    char stringdata14[14];
    char stringdata15[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTrayManagerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTrayManagerENDCLASS_t qt_meta_stringdata_CLASSTrayManagerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "TrayManager"
        QT_MOC_LITERAL(12, 24),  // "showInputWindowRequested"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 26),  // "showHistoryWindowRequested"
        QT_MOC_LITERAL(65, 16),  // "showPetRequested"
        QT_MOC_LITERAL(82, 16),  // "hideAllRequested"
        QT_MOC_LITERAL(99, 15),  // "backupRequested"
        QT_MOC_LITERAL(115, 16),  // "restoreRequested"
        QT_MOC_LITERAL(132, 13),  // "quitRequested"
        QT_MOC_LITERAL(146, 11),  // "onShowInput"
        QT_MOC_LITERAL(158, 13),  // "onShowHistory"
        QT_MOC_LITERAL(172, 9),  // "onShowPet"
        QT_MOC_LITERAL(182, 9),  // "onHideAll"
        QT_MOC_LITERAL(192, 12),  // "onBackupData"
        QT_MOC_LITERAL(205, 13),  // "onRestoreData"
        QT_MOC_LITERAL(219, 6)   // "onQuit"
    },
    "TrayManager",
    "showInputWindowRequested",
    "",
    "showHistoryWindowRequested",
    "showPetRequested",
    "hideAllRequested",
    "backupRequested",
    "restoreRequested",
    "quitRequested",
    "onShowInput",
    "onShowHistory",
    "onShowPet",
    "onHideAll",
    "onBackupData",
    "onRestoreData",
    "onQuit"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTrayManagerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x06,    1 /* Public */,
       3,    0,   99,    2, 0x06,    2 /* Public */,
       4,    0,  100,    2, 0x06,    3 /* Public */,
       5,    0,  101,    2, 0x06,    4 /* Public */,
       6,    0,  102,    2, 0x06,    5 /* Public */,
       7,    0,  103,    2, 0x06,    6 /* Public */,
       8,    0,  104,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,  105,    2, 0x08,    8 /* Private */,
      10,    0,  106,    2, 0x08,    9 /* Private */,
      11,    0,  107,    2, 0x08,   10 /* Private */,
      12,    0,  108,    2, 0x08,   11 /* Private */,
      13,    0,  109,    2, 0x08,   12 /* Private */,
      14,    0,  110,    2, 0x08,   13 /* Private */,
      15,    0,  111,    2, 0x08,   14 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TrayManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSTrayManagerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTrayManagerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTrayManagerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TrayManager, std::true_type>,
        // method 'showInputWindowRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showHistoryWindowRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showPetRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hideAllRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'backupRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restoreRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quitRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onShowInput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onShowHistory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onShowPet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onHideAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBackupData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRestoreData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onQuit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TrayManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrayManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showInputWindowRequested(); break;
        case 1: _t->showHistoryWindowRequested(); break;
        case 2: _t->showPetRequested(); break;
        case 3: _t->hideAllRequested(); break;
        case 4: _t->backupRequested(); break;
        case 5: _t->restoreRequested(); break;
        case 6: _t->quitRequested(); break;
        case 7: _t->onShowInput(); break;
        case 8: _t->onShowHistory(); break;
        case 9: _t->onShowPet(); break;
        case 10: _t->onHideAll(); break;
        case 11: _t->onBackupData(); break;
        case 12: _t->onRestoreData(); break;
        case 13: _t->onQuit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrayManager::*)();
            if (_t _q_method = &TrayManager::showInputWindowRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrayManager::*)();
            if (_t _q_method = &TrayManager::showHistoryWindowRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TrayManager::*)();
            if (_t _q_method = &TrayManager::showPetRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TrayManager::*)();
            if (_t _q_method = &TrayManager::hideAllRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TrayManager::*)();
            if (_t _q_method = &TrayManager::backupRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TrayManager::*)();
            if (_t _q_method = &TrayManager::restoreRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TrayManager::*)();
            if (_t _q_method = &TrayManager::quitRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *TrayManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrayManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTrayManagerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TrayManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TrayManager::showInputWindowRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TrayManager::showHistoryWindowRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TrayManager::showPetRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TrayManager::hideAllRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TrayManager::backupRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void TrayManager::restoreRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TrayManager::quitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
