/****************************************************************************
** Meta object code from reading C++ file 'smtpclient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/smtpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smtpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SmtpClient_t {
    const uint offsetsAndSize[126];
    char stringdata0[910];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SmtpClient_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SmtpClient_t qt_meta_stringdata_SmtpClient = {
    {
QT_MOC_LITERAL(0, 10), // "SmtpClient"
QT_MOC_LITERAL(11, 5), // "error"
QT_MOC_LITERAL(17, 0), // ""
QT_MOC_LITERAL(18, 21), // "SmtpClient::SmtpError"
QT_MOC_LITERAL(40, 1), // "e"
QT_MOC_LITERAL(42, 12), // "stateChanged"
QT_MOC_LITERAL(55, 23), // "SmtpClient::ClientState"
QT_MOC_LITERAL(79, 1), // "s"
QT_MOC_LITERAL(81, 9), // "connected"
QT_MOC_LITERAL(91, 14), // "readyConnected"
QT_MOC_LITERAL(106, 13), // "authenticated"
QT_MOC_LITERAL(120, 8), // "mailSent"
QT_MOC_LITERAL(129, 9), // "mailReset"
QT_MOC_LITERAL(139, 12), // "disconnected"
QT_MOC_LITERAL(152, 18), // "socketStateChanged"
QT_MOC_LITERAL(171, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(200, 5), // "state"
QT_MOC_LITERAL(206, 11), // "socketError"
QT_MOC_LITERAL(218, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(247, 15), // "socketReadyRead"
QT_MOC_LITERAL(263, 15), // "socketEncrypted"
QT_MOC_LITERAL(279, 10), // "AuthMethod"
QT_MOC_LITERAL(290, 9), // "AuthPlain"
QT_MOC_LITERAL(300, 9), // "AuthLogin"
QT_MOC_LITERAL(310, 9), // "SmtpError"
QT_MOC_LITERAL(320, 22), // "ConnectionTimeoutError"
QT_MOC_LITERAL(343, 20), // "ResponseTimeoutError"
QT_MOC_LITERAL(364, 19), // "AuthenticationError"
QT_MOC_LITERAL(384, 16), // "MailSendingError"
QT_MOC_LITERAL(401, 11), // "ServerError"
QT_MOC_LITERAL(413, 11), // "ClientError"
QT_MOC_LITERAL(425, 11), // "SocketError"
QT_MOC_LITERAL(437, 14), // "ConnectionType"
QT_MOC_LITERAL(452, 13), // "TcpConnection"
QT_MOC_LITERAL(466, 13), // "SslConnection"
QT_MOC_LITERAL(480, 13), // "TlsConnection"
QT_MOC_LITERAL(494, 11), // "ClientState"
QT_MOC_LITERAL(506, 16), // "UnconnectedState"
QT_MOC_LITERAL(523, 15), // "ConnectingState"
QT_MOC_LITERAL(539, 14), // "ConnectedState"
QT_MOC_LITERAL(554, 10), // "ReadyState"
QT_MOC_LITERAL(565, 19), // "AuthenticatingState"
QT_MOC_LITERAL(585, 16), // "MailSendingState"
QT_MOC_LITERAL(602, 18), // "DisconnectingState"
QT_MOC_LITERAL(621, 10), // "ResetState"
QT_MOC_LITERAL(632, 11), // "_EHLO_State"
QT_MOC_LITERAL(644, 10), // "_TLS_State"
QT_MOC_LITERAL(655, 16), // "_READY_Connected"
QT_MOC_LITERAL(672, 20), // "_READY_Authenticated"
QT_MOC_LITERAL(693, 15), // "_READY_MailSent"
QT_MOC_LITERAL(709, 16), // "_READY_Encrypted"
QT_MOC_LITERAL(726, 15), // "_TLS_0_STARTTLS"
QT_MOC_LITERAL(742, 14), // "_TLS_1_ENCRYPT"
QT_MOC_LITERAL(757, 11), // "_TLS_2_EHLO"
QT_MOC_LITERAL(769, 13), // "_AUTH_PLAIN_0"
QT_MOC_LITERAL(783, 13), // "_AUTH_LOGIN_0"
QT_MOC_LITERAL(797, 18), // "_AUTH_LOGIN_1_USER"
QT_MOC_LITERAL(816, 18), // "_AUTH_LOGIN_2_PASS"
QT_MOC_LITERAL(835, 12), // "_MAIL_0_FROM"
QT_MOC_LITERAL(848, 17), // "_MAIL_1_RCPT_INIT"
QT_MOC_LITERAL(866, 12), // "_MAIL_2_RCPT"
QT_MOC_LITERAL(879, 12), // "_MAIL_3_DATA"
QT_MOC_LITERAL(892, 17) // "_MAIL_4_SEND_DATA"

    },
    "SmtpClient\0error\0\0SmtpClient::SmtpError\0"
    "e\0stateChanged\0SmtpClient::ClientState\0"
    "s\0connected\0readyConnected\0authenticated\0"
    "mailSent\0mailReset\0disconnected\0"
    "socketStateChanged\0QAbstractSocket::SocketState\0"
    "state\0socketError\0QAbstractSocket::SocketError\0"
    "socketReadyRead\0socketEncrypted\0"
    "AuthMethod\0AuthPlain\0AuthLogin\0SmtpError\0"
    "ConnectionTimeoutError\0ResponseTimeoutError\0"
    "AuthenticationError\0MailSendingError\0"
    "ServerError\0ClientError\0SocketError\0"
    "ConnectionType\0TcpConnection\0SslConnection\0"
    "TlsConnection\0ClientState\0UnconnectedState\0"
    "ConnectingState\0ConnectedState\0"
    "ReadyState\0AuthenticatingState\0"
    "MailSendingState\0DisconnectingState\0"
    "ResetState\0_EHLO_State\0_TLS_State\0"
    "_READY_Connected\0_READY_Authenticated\0"
    "_READY_MailSent\0_READY_Encrypted\0"
    "_TLS_0_STARTTLS\0_TLS_1_ENCRYPT\0"
    "_TLS_2_EHLO\0_AUTH_PLAIN_0\0_AUTH_LOGIN_0\0"
    "_AUTH_LOGIN_1_USER\0_AUTH_LOGIN_2_PASS\0"
    "_MAIL_0_FROM\0_MAIL_1_RCPT_INIT\0"
    "_MAIL_2_RCPT\0_MAIL_3_DATA\0_MAIL_4_SEND_DATA"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SmtpClient[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       4,  106, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   86,    2, 0x06,    1 /* Public */,
       5,    1,   89,    2, 0x06,    3 /* Public */,
       8,    0,   92,    2, 0x06,    5 /* Public */,
       9,    0,   93,    2, 0x06,    6 /* Public */,
      10,    0,   94,    2, 0x06,    7 /* Public */,
      11,    0,   95,    2, 0x06,    8 /* Public */,
      12,    0,   96,    2, 0x06,    9 /* Public */,
      13,    0,   97,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    1,   98,    2, 0x09,   11 /* Protected */,
      17,    1,  101,    2, 0x09,   13 /* Protected */,
      19,    0,  104,    2, 0x09,   15 /* Protected */,
      20,    0,  105,    2, 0x09,   16 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,    1,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
      21,   21, 0x0,    2,  126,
      24,   24, 0x0,    7,  130,
      32,   32, 0x0,    3,  144,
      36,   36, 0x0,   26,  150,

 // enum data: key, value
      22, uint(SmtpClient::AuthPlain),
      23, uint(SmtpClient::AuthLogin),
      25, uint(SmtpClient::ConnectionTimeoutError),
      26, uint(SmtpClient::ResponseTimeoutError),
      27, uint(SmtpClient::AuthenticationError),
      28, uint(SmtpClient::MailSendingError),
      29, uint(SmtpClient::ServerError),
      30, uint(SmtpClient::ClientError),
      31, uint(SmtpClient::SocketError),
      33, uint(SmtpClient::TcpConnection),
      34, uint(SmtpClient::SslConnection),
      35, uint(SmtpClient::TlsConnection),
      37, uint(SmtpClient::UnconnectedState),
      38, uint(SmtpClient::ConnectingState),
      39, uint(SmtpClient::ConnectedState),
      40, uint(SmtpClient::ReadyState),
      41, uint(SmtpClient::AuthenticatingState),
      42, uint(SmtpClient::MailSendingState),
      43, uint(SmtpClient::DisconnectingState),
      44, uint(SmtpClient::ResetState),
      45, uint(SmtpClient::_EHLO_State),
      46, uint(SmtpClient::_TLS_State),
      47, uint(SmtpClient::_READY_Connected),
      48, uint(SmtpClient::_READY_Authenticated),
      49, uint(SmtpClient::_READY_MailSent),
      50, uint(SmtpClient::_READY_Encrypted),
      51, uint(SmtpClient::_TLS_0_STARTTLS),
      52, uint(SmtpClient::_TLS_1_ENCRYPT),
      53, uint(SmtpClient::_TLS_2_EHLO),
      54, uint(SmtpClient::_AUTH_PLAIN_0),
      55, uint(SmtpClient::_AUTH_LOGIN_0),
      56, uint(SmtpClient::_AUTH_LOGIN_1_USER),
      57, uint(SmtpClient::_AUTH_LOGIN_2_PASS),
      58, uint(SmtpClient::_MAIL_0_FROM),
      59, uint(SmtpClient::_MAIL_1_RCPT_INIT),
      60, uint(SmtpClient::_MAIL_2_RCPT),
      61, uint(SmtpClient::_MAIL_3_DATA),
      62, uint(SmtpClient::_MAIL_4_SEND_DATA),

       0        // eod
};

void SmtpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SmtpClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< std::add_pointer_t<SmtpClient::SmtpError>>(_a[1]))); break;
        case 1: _t->stateChanged((*reinterpret_cast< std::add_pointer_t<SmtpClient::ClientState>>(_a[1]))); break;
        case 2: _t->connected(); break;
        case 3: _t->readyConnected(); break;
        case 4: _t->authenticated(); break;
        case 5: _t->mailSent(); break;
        case 6: _t->mailReset(); break;
        case 7: _t->disconnected(); break;
        case 8: _t->socketStateChanged((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketState>>(_a[1]))); break;
        case 9: _t->socketError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 10: _t->socketReadyRead(); break;
        case 11: _t->socketEncrypted(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SmtpClient::*)(SmtpClient::SmtpError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SmtpClient::error)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)(SmtpClient::ClientState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SmtpClient::stateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SmtpClient::connected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SmtpClient::readyConnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SmtpClient::authenticated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SmtpClient::mailSent)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SmtpClient::mailReset)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SmtpClient::disconnected)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject SmtpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SmtpClient.offsetsAndSize,
    qt_meta_data_SmtpClient,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SmtpClient_t
, QtPrivate::TypeAndForceComplete<SmtpClient, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<SmtpClient::SmtpError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<SmtpClient::ClientState, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketState, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *SmtpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SmtpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SmtpClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SmtpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SmtpClient::error(SmtpClient::SmtpError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SmtpClient::stateChanged(SmtpClient::ClientState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SmtpClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SmtpClient::readyConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SmtpClient::authenticated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SmtpClient::mailSent()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SmtpClient::mailReset()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void SmtpClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
