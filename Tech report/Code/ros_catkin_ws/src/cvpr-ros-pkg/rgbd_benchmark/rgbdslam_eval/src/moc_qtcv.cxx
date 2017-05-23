/****************************************************************************
** Meta object code from reading C++ file 'qtcv.h'
**
** Created: Tue Aug 30 17:32:34 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtcv.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UserInterface[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      23,   14,   14,   14, 0x05,
      37,   14,   14,   14, 0x05,
      58,   14,   14,   14, 0x05,
      72,   14,   14,   14, 0x05,
      90,   14,   14,   14, 0x05,
     115,  106,   14,   14, 0x05,
     152,  138,   14,   14, 0x05,
     192,  182,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     211,   14,   14,   14, 0x0a,
     234,   14,   14,   14, 0x0a,
     262,   14,   14,   14, 0x0a,
     284,   14,   14,   14, 0x0a,
     311,   14,   14,   14, 0x0a,
     339,  326,   14,   14, 0x0a,
     399,  388,   14,   14, 0x0a,
     441,  436,   14,   14, 0x0a,
     480,   14,   14,   14, 0x0a,
     497,   14,   14,   14, 0x08,
     508,   14,   14,   14, 0x08,
     518,   14,   14,   14, 0x08,
     527,   14,   14,   14, 0x08,
     537,   14,   14,   14, 0x08,
     554,   14,   14,   14, 0x08,
     569,   14,   14,   14, 0x08,
     581,   14,   14,   14, 0x08,
     600,   14,   14,   14, 0x08,
     608,   14,   14,   14, 0x08,
     615,   14,   14,   14, 0x08,
     642,   14,   14,   14, 0x08,
     659,   14,   14,   14, 0x08,
     677,   14,   14,   14, 0x08,
     696,   14,   14,   14, 0x08,
     713,   14,   14,   14, 0x08,
     740,  734,   14,   14, 0x08,
     759,  734,   14,   14, 0x08,
     777,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UserInterface[] = {
    "UserInterface\0\0reset()\0togglePause()\0"
    "toggleBagRecording()\0getOneFrame()\0"
    "deleteLastFrame()\0sendAllClouds()\0"
    "filename\0saveAllClouds(QString)\0"
    "file_basename\0saveIndividualClouds(QString)\0"
    "max_depth\0setMaxDepth(float)\0"
    "setVisualImage(QImage)\0"
    "setFeatureFlowImage(QImage)\0"
    "setDepthImage(QImage)\0setTransformation(QString)\0"
    "sendFinished()\0pc,transform\0"
    "addPointCloud(const pointcloud_type*,QMatrix4x4)\0"
    "transforms\0updateTransforms(QList<QMatrix4x4>*)\0"
    "list\0setGraphEdges(QList<QPair<int,int> >*)\0"
    "deleteLastNode()\0resetCmd()\0sendAll()\0"
    "setMax()\0saveAll()\0saveIndividual()\0"
    "quickSaveAll()\0pause(bool)\0"
    "bagRecording(bool)\0about()\0help()\0"
    "lastTransformationMatrix()\0setInfo(QString)\0"
    "setInfo2(QString)\0setStatus(QString)\0"
    "getOneFrameCmd()\0deleteLastFrameCmd()\0"
    "is_on\0set3DDisplay(bool)\0set2DStream(bool)\0"
    "toggleTriangulation()\0"
};

const QMetaObject UserInterface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UserInterface,
      qt_meta_data_UserInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UserInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UserInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UserInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserInterface))
        return static_cast<void*>(const_cast< UserInterface*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UserInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: reset(); break;
        case 1: togglePause(); break;
        case 2: toggleBagRecording(); break;
        case 3: getOneFrame(); break;
        case 4: deleteLastFrame(); break;
        case 5: sendAllClouds(); break;
        case 6: saveAllClouds((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: saveIndividualClouds((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: setMaxDepth((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: setVisualImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 10: setFeatureFlowImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 11: setDepthImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 12: setTransformation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: sendFinished(); break;
        case 14: addPointCloud((*reinterpret_cast< const pointcloud_type*(*)>(_a[1])),(*reinterpret_cast< QMatrix4x4(*)>(_a[2]))); break;
        case 15: updateTransforms((*reinterpret_cast< QList<QMatrix4x4>*(*)>(_a[1]))); break;
        case 16: setGraphEdges((*reinterpret_cast< QList<QPair<int,int> >*(*)>(_a[1]))); break;
        case 17: deleteLastNode(); break;
        case 18: resetCmd(); break;
        case 19: sendAll(); break;
        case 20: setMax(); break;
        case 21: saveAll(); break;
        case 22: saveIndividual(); break;
        case 23: quickSaveAll(); break;
        case 24: pause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: bagRecording((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: about(); break;
        case 27: help(); break;
        case 28: lastTransformationMatrix(); break;
        case 29: setInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: setInfo2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: setStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 32: getOneFrameCmd(); break;
        case 33: deleteLastFrameCmd(); break;
        case 34: set3DDisplay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: set2DStream((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: toggleTriangulation(); break;
        default: ;
        }
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void UserInterface::reset()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UserInterface::togglePause()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void UserInterface::toggleBagRecording()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void UserInterface::getOneFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void UserInterface::deleteLastFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void UserInterface::sendAllClouds()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void UserInterface::saveAllClouds(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void UserInterface::saveIndividualClouds(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void UserInterface::setMaxDepth(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
