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
#ifndef FLUGS_HTTPSERVER_CONNECTION_H
#define FLUGS_HTTPSERVER_CONNECTION_H

#include "flugs_httpserver_export.h"
#include <Flugs/Foundation/Connection>
#include <Flugs/HttpServer/HttpServer>

class QTcpSocket;

FLUGS_BEGIN_NAMESPACE

class HttpServerConnectionPrivate;

/**
 * @brief A connection in the server.
 */
class FLUGS_HTTPSERVER_EXPORT HttpServerConnection : public Connection
{
    Q_OBJECT
    Q_DISABLE_COPY(HttpServerConnection)

public:
    virtual ~HttpServerConnection();
    void close() override;
    void setTimeout(int msecs) override;
    QAbstractSocket* socket() const;

protected:
    explicit HttpServerConnection(HttpServer* parent);
    explicit HttpServerConnection(QTcpSocket* socket, HttpServer* parent);
    explicit HttpServerConnection(HttpServerConnectionPrivate&, HttpServer* server);

    void setSocket(QTcpSocket* socket);
    void timerEvent(QTimerEvent*) override;

    friend class HttpServer;
    Q_DECLARE_PRIVATE(HttpServerConnection)
    QScopedPointer<HttpServerConnectionPrivate> d_ptr;
};

FLUGS_END_NAMESPACE

#endif
