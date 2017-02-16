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
#ifndef FLUGS_FOUNDATION_RESPONSE_H
#define FLUGS_FOUNDATION_RESPONSE_H

#include <Flugs/Foundation/Connection>
#include <Flugs/Foundation/Headers>
#include <Flugs/Foundation/Status>

#include <QtCore/QDateTime>
#include <QtCore/QFileInfo>
#include <QtCore/QMimeType>
#include <QtNetwork/QTcpSocket>

FLUGS_BEGIN_NAMESPACE

/**
 * The Response class handles sending data back to the client
 * as a response to a request.
 *
 * @sa Connection
 */
class FLUGS_FOUNDATION_EXPORT Response : public QObject
{
    Q_OBJECT

public:
    /**
     *
     */
    explicit Response(QObject* parent = nullptr);

    /**
     *
     */
    virtual ~Response();

    /**
     *
     */
    virtual bool isFinished() const = 0;

    /**
     * @brief The response HTTP status code
     */
    virtual Status status() const = 0;

    /**
     * @brief The HTTP version
     */
    virtual QVersionNumber version() const = 0;

    /**
     * @brief Returns all the headers that already been set
     */
    virtual Headers& headers() = 0;

    /**
     * @brief Returns all the headers that already been set
     */
    virtual const Headers& headers() const = 0;

    /**
     * writes a block of data into the HTTP packet.
     * @note headers are written (flushed) before any data.
     * @warning after calling this method add a new header, set status code, set
     * Url have no effect!
     */
    virtual void write(const char* data, qint64 size) = 0;

    inline void write(const QByteArray& data)
    {
        write(data.constData(), data.size());
    }

    qint64 write(QIODevice* dev);

    bool writeFile(const QFileInfo& file, const QMimeType& mimeType = QMimeType());

    /**
     * ends (finishes) the outgoing packet by calling write().
     * headers and data will be flushed to the underlying socket.
     *
     * @sa write()
     */
    virtual void end(const QByteArray& data = QByteArray()) = 0;

    /** returns the parent Connection object. */
    virtual Connection* connection() = 0;

    // helper methods
    void notFound()
    {
        setStatusCode(Status::NotFound);
        end();
    }

    void redirect(const QUrl& to, Status::Code code = Status::Code::TemporaryRedirect)
    {
    }
    void forbidden()
    {
    }

public slots:
    /**
     * @brief Set the response HTTP status code
     */
    virtual void setStatus(const Status& code) = 0;

    /**
     * @brief Set the response HTTP status code
     */
    void setStatusCode(Status::Code code);

    /**
     * @brief Set the HTTP version
     */
    virtual void setVersion(const QVersionNumber& version) = 0;

signals:
    /**
     * Emitted when all the data has been sent.
     * this signal indicates that the underlaying socket has transmitted all
     *  of it's buffered data.
     */
    void allBytesWritten();

    /**
     * Emitted when the packet is finished and reports if it was the last packet.
     *
     * if it was the last packet (google for "Connection: keep-alive / close")
     * the http connection (socket) will be closed automatically.
     */
    void done(bool wasTheLastPacket);
};

FLUGS_END_NAMESPACE

#endif
