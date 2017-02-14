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
#include "httpserverconnection.h"
#include "httpserverconnection_p.h"

FLUGS_USE_NAMESPACE

HttpServerConnection::HttpServerConnection(HttpServer* parent)
    : HttpServerConnection(nullptr, parent)
{
}

HttpServerConnection::HttpServerConnection(QTcpSocket* s, HttpServer* parent)
    : Connection(parent)
    , d_ptr(new HttpServerConnectionPrivate(s, this, parent))
{
}

HttpServerConnection::HttpServerConnection(HttpServerConnectionPrivate& dd, HttpServer* parent)
    : Connection(parent)
    , d_ptr(&dd)
{
}

HttpServerConnection::~HttpServerConnection()
{
}

void HttpServerConnection::setSocket(QTcpSocket* socket)
{
    d_ptr->setSocket(socket);
}

void HttpServerConnection::setTimeout(int msecs)
{
    Q_D(HttpServerConnection);

    Connection::setTimeout(msecs);

    if (timeout() > 0) {
        d->timer.start(timeout(), Qt::CoarseTimer, this);
    }
    else {
        d->timer.stop();
    }
}

void HttpServerConnection::close()
{
    Q_D(HttpServerConnection);

    if (d->socket->isOpen()) {
        d->socket->close();
    }
}

QAbstractSocket* HttpServerConnection::socket() const
{
    return d_func()->socket;
}

void HttpServerConnection::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    qCDebug(LogHttpConnection) << "timeout event occurred";
    close();
}
