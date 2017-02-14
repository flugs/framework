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
#ifndef FLUGS_HTTPSERVER_SERVER_H
#define FLUGS_HTTPSERVER_SERVER_H

#include "flugs_httpserver_export.h"
#include <Flugs/Foundation/Server>

// Not really necessary here, but the users will need it anyway.
// So it makes it easier to use Flugs.
#include <Flugs/Foundation/Request>
#include <Flugs/Foundation/Response>

class QTcpServer;

#if FLUGS_WIP
class QSslCertificate;
class QSslKey;
#endif

FLUGS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(LogHttpServer)
Q_DECLARE_LOGGING_CATEGORY(LogHttpConnection)
Q_DECLARE_LOGGING_CATEGORY(LogHttpRequest)
Q_DECLARE_LOGGING_CATEGORY(LogHttpResponse)

class Connection;
class HttpServerPrivate;

/**
 * @brief
 */
class FLUGS_HTTPSERVER_EXPORT HttpServer : public Server
{
    Q_OBJECT
    Q_DISABLE_COPY(HttpServer)

public:
    explicit HttpServer(QObject* parent = nullptr);
    virtual ~HttpServer();

    /**
     * @brief Tells the server to listen for incoming http connections
     *
     * @param address The address the server will listen on
     * @param port    The port the server will liste on
     *
     * @return Returns true on success; otherwise returns false.
     */
    bool listen(const QHostAddress& address, quint16 port);

    /**
     * @overload void listen(quint16 port)
     */
    bool listen(quint16 port)
    {
        return listen(QHostAddress::Any, port);
    }

#if FLUGS_WIP
    /**
     * @brief Tells the server to listen for incoming secured https connections
     *
     * @param address     The address the server will listen on
     * @param port        The port the server will liste on
     * @param certificate The certificate
     * @param key         The private key
     *
     * @return Returns true on success; otherwise returns false.
     */
    bool listenTls(const QHostAddress& address, quint16 port, const QSslCertificate& certificate, const QSslKey& key);

    /**
     * @overload listenTls(const QHostAddress& address, quint16 port)
     */
    bool listenTls(const QHostAddress& address, quint16 port)
    {
        return listenTls(address, port, handler());
    }

    /**
     * @overload listenTls(quint16 port, const QSslCertificate &certificate, const QSslKey &key)
     */
    bool listenTls(quint16 port, const QSslCertificate& certificate, const QSslKey& key)
    {
        return listenTls(QHostAddress::Any, port, certificate, key, handler());
    }

    /**
     * @overload listenTls(quint16 port)
     */
    bool listenTls(quint16 port)
    {
        return listenTls(QHostAddress::Any, port, handler());
    }

    /**
     * @brief Tells the server to listen for secured incoming connections using key and certification taken from letsencrypt.org
     *
     * @return Returns true on success; otherwise returns false.
     */
    bool listenLetsEncrypt(const QHostAddress& address, quint16 port);

    /**
     * @overload listenLetsEncrypt(quint16 port)
     */
    bool listenLetsEncrypt(quint16 port)
    {
        return listenLetsEncrypt(QHostAddress::Any, port);
    }

    /**
     * @brief Tells the server to listen for incoming connections on the socket @p name
     *
     * On Unix @p name is a named pipe and on Windows @p name is a named pipe.
     *
     * @return Returns true on success; otherwise returns false.
     */
    bool listenUnix(const QString& name);

    /**
     * @brief Tells the server to listen for incoming connections on the given socket
     *
     * @param socketDescriptor The socket the server will listen on
     *
     * @return Returns true on success; otherwise returns false.
     */
    bool listenSocket(qintptr& socketDescriptor);

#endif

    bool isListening() const override;
    void close() override;

    QAbstractSocket::SocketError serverError() const override;
    QString errorString() const override;

protected slots:
    void onNewConnection();

protected:
    /**
     * Is called when server accepts a new connection.
     * you can override this function for using a thread-pool or ... some other
     * reasons.
     *
     * the default implementation just connects Connection::newRequest signal.
     *
     * @note if you override this method, the signal won't be emitted by Flugs
     * (perhaps, you do not need it anymore)
     *
     * @param connection New incoming connection.
     */
    virtual void incomingConnection(Connection* connection);

protected:
    QTcpServer* m_server = nullptr;
};

FLUGS_END_NAMESPACE

#endif
