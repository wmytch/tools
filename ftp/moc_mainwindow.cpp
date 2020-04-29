/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata0[442];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 20), // "on_pbConnect_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "onConnected"
QT_MOC_LITERAL(4, 45, 17), // "onConnectionError"
QT_MOC_LITERAL(5, 63, 14), // "QSsh::SshError"
QT_MOC_LITERAL(6, 78, 3), // "err"
QT_MOC_LITERAL(7, 82, 20), // "onChannelInitialized"
QT_MOC_LITERAL(8, 103, 14), // "onChannelError"
QT_MOC_LITERAL(9, 118, 9), // "errString"
QT_MOC_LITERAL(10, 128, 12), // "onOpfinished"
QT_MOC_LITERAL(11, 141, 15), // "QSsh::SftpJobId"
QT_MOC_LITERAL(12, 157, 15), // "onDataAvailable"
QT_MOC_LITERAL(13, 173, 19), // "onFileInfoAvailable"
QT_MOC_LITERAL(14, 193, 25), // "QList<QSsh::SftpFileInfo>"
QT_MOC_LITERAL(15, 219, 34), // "on_cbLocalPath_currentIndexCh..."
QT_MOC_LITERAL(16, 254, 4), // "arg1"
QT_MOC_LITERAL(17, 259, 26), // "on_localView_doubleClicked"
QT_MOC_LITERAL(18, 286, 11), // "QModelIndex"
QT_MOC_LITERAL(19, 298, 5), // "index"
QT_MOC_LITERAL(20, 304, 28), // "on_tbLocalParentPath_clicked"
QT_MOC_LITERAL(21, 333, 37), // "on_remoteFileSystem_itemDoubl..."
QT_MOC_LITERAL(22, 371, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(23, 388, 4), // "item"
QT_MOC_LITERAL(24, 393, 6), // "column"
QT_MOC_LITERAL(25, 400, 19), // "on_pbUpload_clicked"
QT_MOC_LITERAL(26, 420, 21) // "on_pbDownload_clicked"

    },
    "MainWindow\0on_pbConnect_clicked\0\0"
    "onConnected\0onConnectionError\0"
    "QSsh::SshError\0err\0onChannelInitialized\0"
    "onChannelError\0errString\0onOpfinished\0"
    "QSsh::SftpJobId\0onDataAvailable\0"
    "onFileInfoAvailable\0QList<QSsh::SftpFileInfo>\0"
    "on_cbLocalPath_currentIndexChanged\0"
    "arg1\0on_localView_doubleClicked\0"
    "QModelIndex\0index\0on_tbLocalParentPath_clicked\0"
    "on_remoteFileSystem_itemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_pbUpload_clicked\0on_pbDownload_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    1,   86,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    1,   90,    2, 0x08 /* Private */,
      10,    2,   93,    2, 0x08 /* Private */,
      12,    2,   98,    2, 0x08 /* Private */,
      13,    2,  103,    2, 0x08 /* Private */,
      15,    1,  108,    2, 0x08 /* Private */,
      17,    1,  111,    2, 0x08 /* Private */,
      20,    0,  114,    2, 0x08 /* Private */,
      21,    2,  115,    2, 0x08 /* Private */,
      25,    0,  120,    2, 0x08 /* Private */,
      26,    0,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 14,    2,    2,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22, QMetaType::Int,   23,   24,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pbConnect_clicked(); break;
        case 1: _t->onConnected(); break;
        case 2: _t->onConnectionError((*reinterpret_cast< QSsh::SshError(*)>(_a[1]))); break;
        case 3: _t->onChannelInitialized(); break;
        case 4: _t->onChannelError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onOpfinished((*reinterpret_cast< QSsh::SftpJobId(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->onDataAvailable((*reinterpret_cast< QSsh::SftpJobId(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->onFileInfoAvailable((*reinterpret_cast< QSsh::SftpJobId(*)>(_a[1])),(*reinterpret_cast< const QList<QSsh::SftpFileInfo>(*)>(_a[2]))); break;
        case 8: _t->on_cbLocalPath_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_localView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 10: _t->on_tbLocalParentPath_clicked(); break;
        case 11: _t->on_remoteFileSystem_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->on_pbUpload_clicked(); break;
        case 13: _t->on_pbDownload_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
