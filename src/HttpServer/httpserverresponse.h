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
#ifndef FLUGS_HTTPSERVER_RESPONSE_H
#define FLUGS_HTTPSERVER_RESPONSE_H

#include "flugs_httpserver_export.h"
#include <Flugs/Foundation/Response>

FLUGS_BEGIN_NAMESPACE

class HttpServerConnection;

class FLUGS_HTTPSERVER_EXPORT HttpServerResponse : public Response
{
    Q_OBJECT

public:
    virtual ~HttpServerResponse();

    Status status() const override;
    QVersionNumber version() const override;
    Headers& headers() override;
    const Headers& headers() const override;
    void write(const char* data, qint64 size) override;
    void end(const QByteArray& data = QByteArray()) override;
    Connection* connection() override;

public slots:
    void setStatus(const Status& status) override;
    void setVersion(const QVersionNumber& version) override;

protected:
    bool writeData(const QByteArray& data);
    bool endPacket(const QByteArray& data);

protected:
    explicit HttpServerResponse(HttpServerConnection*);
    friend class HttpServerConnectionPrivate;

    QAbstractSocket* socket = nullptr;
    HttpServerConnection* m_connection = nullptr;
    QVersionNumber m_httpVersion;
    Headers m_headers;
    Status m_status;
    bool m_finished = false;
    bool m_headerWritten = false;
    bool m_keepAlive = false;
};

FLUGS_END_NAMESPACE

#endif
