/****************************************************************************
**
** This file is part of Flugs.
**
** Copyright 2017 Stefan Böhmann <sboehmann@flugs.io>
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
#ifndef FLUGS_MIDDLEWARE_GZIP_H
#define FLUGS_MIDDLEWARE_GZIP_H

#include <Flugs/Foundation/Middleware>

FLUGS_BEGIN_NAMESPACE

class GzipResponse : public Response
{
    Q_OBJECT

public:
    GzipResponse(Response* r)
        : m_response(r)
    {
    }

    ~GzipResponse()
    {
    }

    bool isFinished() const override
    {
        return m_response->isFinished();
    }

    Status status() const override
    {
        return m_response->status();
    }

    QVersionNumber version() const override
    {
        return m_response->version();
    }

    Headers& headers() override
    {
        return m_response->headers();
    }

    const Headers& headers() const override
    {
        return m_response->headers();
    }

    void write(const char* data, qint64 size) override
    {
        m_response->write(data, size);
    }

    void end(const QByteArray& data = QByteArray()) override
    {
        m_response->end();
    }

    virtual Connection* connection() override
    {
        return m_response->connection();
    }

public slots:
    virtual void setStatus(const Status& code) override
    {
        m_response->setStatus(code);
    }

    virtual void setVersion(const QVersionNumber& version)
    {
        m_response->setVersion(version);
    }

private:
    Response* m_response;
};

class Gzip : public Middleware
{
    Q_OBJECT

protected:
    void handle(Request request, Response* response) override
    {
        GzipResponse gz(response);
        next(request, &gz);

        // response->setHeader(Header::ContentLenght, "");
        // gzw.Header().Del("Content-Length");
    }
};

FLUGS_END_NAMESPACE

#endif
