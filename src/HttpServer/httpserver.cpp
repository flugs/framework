/****************************************************************************
**
** This file is part of Flugs.
**
** Copyright 2016, 2017 Stefan Böhmann <sboehmann@flugs.io>
**
** Contact: http://www.flugs.io/licensing
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#include "httpserver.h"
#include "httpserverconnection.h"
#include "httpserverresponse.h"

#include <QtCore/QMetaMethod>
#include <QtNetwork/QTcpServer>

FLUGS_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(LogHttpServer, FLUGS_ROOT_LOGGING_CATEGORY ".Http.Server")
Q_LOGGING_CATEGORY(LogHttpConnection, FLUGS_ROOT_LOGGING_CATEGORY ".Http.Connection")
Q_LOGGING_CATEGORY(LogHttpRequest, FLUGS_ROOT_LOGGING_CATEGORY ".Http.Request")
Q_LOGGING_CATEGORY(LogHttpResponse, FLUGS_ROOT_LOGGING_CATEGORY ".Http.Response")

HttpServer::HttpServer(QObject* parent)
    : Server(parent)
{
    qCDebug(LogHttpServer) << "Http server instance created.";
}

HttpServer::~HttpServer()
{
    close();

    qCDebug(LogHttpServer) << "Http server instance destroyed.";
    delete m_server;
}

bool HttpServer::listen(const QHostAddress& address, quint16 port)
{
    qCDebug(LogHttpServer).noquote() << QString(QStringLiteral("Start listening on 'http://%1:%2'.")).arg(address.toString()).arg(port);

    if (Q_UNLIKELY(!m_server)) {
        m_server = new QTcpServer(this);
        connect(m_server, &QTcpServer::acceptError, this, &HttpServer::acceptError);
        connect(m_server, &QTcpServer::newConnection, this, &HttpServer::onNewConnection);
    }

    if (!m_server->listen(address, port)) {
        qCInfo(LogHttpServer).noquote() << "Failed to start server:" << m_server->errorString();
        return false;
    }

    return true;
}

#if FLUGS_WIP

bool Flugs::listenTls(const QHostAddress& address, quint16 port, const QSslCertificate& certificate, const QSslKey& key)
{
    Q_UNUSED(address)
    Q_UNUSED(port)
    Q_UNUSED(certificate)
    Q_UNUSED(key)
    Q_UNUSED(handler)

    return false;
}

bool Flugs::listenTls(const QHostAddress& address, quint16 port)
{
    Q_UNUSED(address)
    Q_UNUSED(port)

    return false;
}

bool Flugs::listenLetsEncrypt(const QHostAddress& address, quint16 port)
{
    Q_UNUSED(address)
    Q_UNUSED(port)
    Q_UNUSED(handler)

    return false;
}

bool Flugs::listenUnix(const QString& name)
{
    Q_UNUSED(name)
    Q_UNUSED(handler)

    return false;
}

bool Flugs::listenSocket(qintptr& socketDescriptor)
{
    Q_UNUSED(socketDescriptor)
    Q_UNUSED(handler)

    return false;
}

#endif

bool HttpServer::isListening() const
{
    return m_server && m_server->isListening();
}

void HttpServer::close()
{
    if (m_server) {
        qCDebug(LogHttpServer) << "closing http server socket.";
        m_server->close();
    }
}

QAbstractSocket::SocketError HttpServer::serverError() const
{
    if (m_server) {
        return m_server->serverError();
    }

    return QAbstractSocket::UnknownSocketError;
}

QString HttpServer::errorString() const
{
    if (m_server) {
        return m_server->errorString();
    }

    return QString();
}

void HttpServer::onNewConnection()
{
    QTcpSocket* socket = nullptr;
    while ((socket = m_server->nextPendingConnection()) != nullptr) {
        qCDebug(LogHttpServer) << "incomming http server connection on socket descriptor:" << socket->socketDescriptor();

        HttpServerConnection* connection = new HttpServerConnection(socket, this);
        connection->setTimeout(timeout());

        emit newConnection(connection);
        incomingConnection(connection);
    }
}

void HttpServer::incomingConnection(Connection* connection)
{
    connect(connection, &Connection::newRequest, this, &HttpServer::newRequest);
}

FLUGS_END_NAMESPACE
