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
#ifndef FLUGS_HTTPSERVER_HTTPSERVERCONNECTION_PRIVATE_H
#define FLUGS_HTTPSERVER_HTTPSERVERCONNECTION_PRIVATE_H

#include <Flugs/Foundation/AbstractHttpParser>
#include <Flugs/Foundation/Request>

#include <Flugs/HttpServer/HttpServer>
#include <Flugs/HttpServer/HttpServerConnection>
#include <Flugs/HttpServer/HttpServerResponse>

#include <QBasicTimer>

FLUGS_BEGIN_NAMESPACE

class HttpServerConnectionPrivate : protected AbstractHttpParser
{
    Q_DECLARE_PUBLIC(HttpServerConnection)

public:
    virtual ~HttpServerConnectionPrivate()
    {
    }

public:
    explicit HttpServerConnectionPrivate(QTcpSocket* s, HttpServerConnection* q, HttpServer* server)
        : q_ptr(q)
        , server(server)
    {
        QObject::connect(q_func(), &Connection::disconnected, [this]() { release(); });

        setSocket(s);
    }

    void setSocket(QAbstractSocket* s)
    {
        socket = s;

        QObject::connect(socket, &QTcpSocket::readyRead, [this]() { onReadyRead(); });

        QObject::connect(socket, &QTcpSocket::bytesWritten, [this]() {
            qint64 btw = socket->bytesToWrite();

            if (btw == 0 && lastResponse) {
                emit lastResponse->allBytesWritten();
            }
        });

        QObject::connect(socket, &QTcpSocket::disconnected, q_func(), &Connection::disconnected, Qt::QueuedConnection);
    }

    void release()
    {
        QObject::disconnect(socket, 0, 0, 0);
        socket->close();
        socket->deleteLater();

        lastRequest.clear();

        if (lastResponse) {
            lastResponse->deleteLater();
            lastResponse = nullptr;
        }

        q_func()->deleteLater();
    }

public:
    void onReadyRead()
    {
        while (socket->bytesAvailable() > 0) {
            char buffer[4097] = { 0 };
            size_t readLength = (size_t)socket->read(buffer, 4096);

            parse(buffer, readLength);
        }
    }

    bool onMessageBegin() override
    {
        currentUrl.clear();
        currentUrl.reserve(128);
        lastRequest.clear();
        return true;
    }

    bool onUrl(const QByteArray& data) override
    {
        currentUrl.append(data);
        return true;
    }

    bool onHeaderValue(const QByteArray& name, const QByteArray& value) override
    {
        lastRequest.addHeader(name, value);
        return true;
    }

    bool onHeadersComplete() override
    {
        lastRequest.setUrl(QUrl::fromEncoded(currentUrl));
        lastRequest.setMethod(method());
        lastRequest.setHttpVersion(QVersionNumber(httpMajor(), httpMinor()));

        // set client information
        lastRequest.setRemoteAddress(socket->peerAddress());
        lastRequest.setRemotePort(socket->peerPort());

        if (lastResponse) {
            lastResponse->deleteLater();
            lastResponse = nullptr;
        }

        lastResponse = new HttpServerResponse(q_func());

        if (httpMajor() < 1 || httpMinor() < 1) {
            lastResponse->m_keepAlive = false;
        }

        // close the connection if response was the last packet
        QObject::connect(lastResponse, &Response::done, [this](bool wasTheLastPacket) {
            keepAlive = !wasTheLastPacket;
            if (wasTheLastPacket) {
                socket->flush();
                socket->close();
            }
        });

        return true;
    }

    bool onBody(const QByteArray& data) override
    {
        lastRequest.appendBody(data);
        return true;
    }

    bool onMessageComplete() override
    {
        emit q_func()->newRequest(lastRequest, lastResponse);
        return true;
    }

protected:
    HttpServerConnection* const q_ptr;
    HttpServer* const server;

    // Since there can only be one request/response pair per connection at any
    // time even with pipelining.
    Request lastRequest;
    HttpServerResponse* lastResponse = nullptr;

    QBasicTimer timer;
    QAbstractSocket* socket = nullptr;
    bool keepAlive = false;

private:
    QByteArray currentUrl;
};

FLUGS_END_NAMESPACE

#endif
