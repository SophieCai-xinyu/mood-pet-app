/****************************************************************************
** Meta object code from reading C++ file 'HistoryWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "HistoryWindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HistoryWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
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
struct qt_meta_tag_ZN13HistoryWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto HistoryWindow::qt_create_metaobjectdata<qt_meta_tag_ZN13HistoryWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "HistoryWindow",
        "onSearchTextChanged",
        "",
        "text",
        "onFilterChanged",
        "filter",
        "onItemClicked",
        "QListWidgetItem*",
        "item",
        "onExportClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onSearchTextChanged'
        QtMocHelpers::SlotData<void(const QString &)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'onFilterChanged'
        QtMocHelpers::SlotData<void(const QString &)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'onItemClicked'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Slot 'onExportClicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<HistoryWindow, qt_meta_tag_ZN13HistoryWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject HistoryWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13HistoryWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13HistoryWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13HistoryWindowE_t>.metaTypes,
    nullptr
} };

void HistoryWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<HistoryWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onSearchTextChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->onFilterChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->onItemClicked((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 3: _t->onExportClicked(); break;
        default: ;
        }
    }
}

const QMetaObject *HistoryWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistoryWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13HistoryWindowE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HistoryWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
