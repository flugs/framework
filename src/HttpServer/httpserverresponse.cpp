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
#include "httpserverresponse.h"
#include "httpserverconnection.h"

FLUGS_USE_NAMESPACE

HttpServerResponse::HttpServerResponse(HttpServerConnection* conn)
    : Response(conn)
    , m_connection(conn)
    , m_httpVersion(1, 1)
    , m_status(Status::Ok)
{
    socket = m_connection->socket();
    QObject::connect(m_connection, &Connection::disconnected, this, &Response::deleteLater);
}

HttpServerResponse::~HttpServerResponse()
{
}

Status HttpServerResponse::status() const
{
    return m_status;
}

void HttpServerResponse::setStatus(const Status& s)
{
    m_status = s;
}

QVersionNumber HttpServerResponse::version() const
{
    return m_httpVersion;
}

void HttpServerResponse::setVersion(const QVersionNumber& version)
{
    m_httpVersion = version;
}

Headers& HttpServerResponse::headers()
{
    return m_headers;
}

const Headers& HttpServerResponse::headers() const
{
    return m_headers;
}

void HttpServerResponse::write(const char* data, qint64 size)
{
    writeData(data);
}

void HttpServerResponse::end(const QByteArray& data)
{
    if (endPacket(data)) {
        emit done(!m_keepAlive);
    }
}

Connection* HttpServerResponse::connection()
{
    return m_connection;
}

bool HttpServerResponse::writeData(const QByteArray& data)
{
    if (m_finished) {
        return false;
    }

    // ensure that the header is send
    if (!m_headerWritten) {
        const QString http = QString(QStringLiteral("HTTP/%1.%2 %3 %4\r\n")).arg(m_httpVersion.majorVersion()).arg(m_httpVersion.minorVersion()).arg(m_status.number()).arg(m_status.reasonPhrase());
        socket->write(http.toLatin1());

        if (m_headers.contains(QByteArrayLiteral("connection"), QByteArrayLiteral("keep-alive"))) {
            m_keepAlive = true;
        }
        else if (!m_headers.contains(QByteArrayLiteral("connection"), QByteArrayLiteral("close"))) {
            m_headers.insert(QByteArrayLiteral("connection"), QByteArrayLiteral("close"));
        }

        if (!m_headers.contains(QByteArrayLiteral("date"))) {
            // Sun, 06 Nov 1994 08:49:37 GMT
            // RFC 822. Use QLocale::c() so english is used for month and day.
            QString str = QLocale::c().toString(QDateTime::currentDateTimeUtc(), QStringLiteral("ddd, dd MMM yyyy hh:mm:ss")).append(QStringLiteral(" GMT"));

            m_headers.insert(QByteArrayLiteral("date"), str.toLatin1());
        }

        const auto h = m_headers.headers();
        for (auto it = h.constBegin(); it != h.constEnd(); ++it) {
            const QByteArray buffer = it->name() + QByteArrayLiteral(": ") + it->value() + QByteArrayLiteral("\r\n");
            socket->write(buffer);
        }

        socket->write("\r\n");
        m_headerWritten = true;
    }

    socket->write(data);
    return true;
}

bool HttpServerResponse::endPacket(const QByteArray& data)
{
    if (!writeData(data)) {
        return false;
    }

    socket->flush();
    m_finished = true;

    return true;
}
