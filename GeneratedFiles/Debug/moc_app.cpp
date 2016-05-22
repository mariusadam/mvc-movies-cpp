/****************************************************************************
** Meta object code from reading C++ file 'app.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/gui/app.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'app.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_App_t {
    QByteArrayData data[18];
    char stringdata0[435];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_App_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_App_t qt_meta_stringdata_App = {
    {
QT_MOC_LITERAL(0, 0, 3), // "App"
QT_MOC_LITERAL(1, 4, 22), // "__on_addButton_clicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 30), // "__on_selectedTableCell_clicked"
QT_MOC_LITERAL(4, 59, 5), // "index"
QT_MOC_LITERAL(5, 65, 25), // "__on_deleteButton_clicked"
QT_MOC_LITERAL(6, 91, 25), // "__on_searchButton_clicked"
QT_MOC_LITERAL(7, 117, 23), // "__on_quitButton_clicked"
QT_MOC_LITERAL(8, 141, 33), // "__on_generateRandomButton_cli..."
QT_MOC_LITERAL(9, 175, 25), // "__on_updateButton_clicked"
QT_MOC_LITERAL(10, 201, 23), // "__on_undoButton_clicked"
QT_MOC_LITERAL(11, 225, 23), // "__on_sortButton_clicked"
QT_MOC_LITERAL(12, 249, 28), // "__on_addToCartButton_clicked"
QT_MOC_LITERAL(13, 278, 29), // "__on_manageCartButton_clicked"
QT_MOC_LITERAL(14, 308, 33), // "__on_fillCartRandomButton_cli..."
QT_MOC_LITERAL(15, 342, 33), // "__on_deleteFromCartButton_cli..."
QT_MOC_LITERAL(16, 376, 28), // "__on_clearCartButton_clicked"
QT_MOC_LITERAL(17, 405, 29) // "__on_exportCartButton_clicked"

    },
    "App\0__on_addButton_clicked\0\0"
    "__on_selectedTableCell_clicked\0index\0"
    "__on_deleteButton_clicked\0"
    "__on_searchButton_clicked\0"
    "__on_quitButton_clicked\0"
    "__on_generateRandomButton_clicked\0"
    "__on_updateButton_clicked\0"
    "__on_undoButton_clicked\0__on_sortButton_clicked\0"
    "__on_addToCartButton_clicked\0"
    "__on_manageCartButton_clicked\0"
    "__on_fillCartRandomButton_clicked\0"
    "__on_deleteFromCartButton_clicked\0"
    "__on_clearCartButton_clicked\0"
    "__on_exportCartButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_App[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    1,   90,    2, 0x08 /* Private */,
       5,    0,   93,    2, 0x08 /* Private */,
       6,    0,   94,    2, 0x08 /* Private */,
       7,    0,   95,    2, 0x08 /* Private */,
       8,    0,   96,    2, 0x08 /* Private */,
       9,    0,   97,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    0,   99,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    0,  103,    2, 0x08 /* Private */,
      16,    0,  104,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void App::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        App *_t = static_cast<App *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->__on_addButton_clicked(); break;
        case 1: _t->__on_selectedTableCell_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->__on_deleteButton_clicked(); break;
        case 3: _t->__on_searchButton_clicked(); break;
        case 4: _t->__on_quitButton_clicked(); break;
        case 5: _t->__on_generateRandomButton_clicked(); break;
        case 6: _t->__on_updateButton_clicked(); break;
        case 7: _t->__on_undoButton_clicked(); break;
        case 8: _t->__on_sortButton_clicked(); break;
        case 9: _t->__on_addToCartButton_clicked(); break;
        case 10: _t->__on_manageCartButton_clicked(); break;
        case 11: _t->__on_fillCartRandomButton_clicked(); break;
        case 12: _t->__on_deleteFromCartButton_clicked(); break;
        case 13: _t->__on_clearCartButton_clicked(); break;
        case 14: _t->__on_exportCartButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject App::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_App.data,
      qt_meta_data_App,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *App::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *App::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_App.stringdata0))
        return static_cast<void*>(const_cast< App*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int App::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
