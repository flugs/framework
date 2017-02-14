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
#ifndef FLUGS_FOUNDATION_CONNECTION_H
#define FLUGS_FOUNDATION_CONNECTION_H

#include <Flugs/Foundation/Global>
#include <Flugs/Foundation/Request>

FLUGS_BEGIN_NAMESPACE

class Response;

class FLUGS_FOUNDATION_EXPORT Connection : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Connection)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)

public:
    /**
     * @brief Destroys the connection.
     */
    virtual ~Connection();

    /**
     * @brief Returns the timeout.
     */
    int timeout() const;

    /**
     * @brief Close the connection.
     */
    virtual void close() = 0;

public slots:
    /**
     * @brief Set an optional timeout for this connection.
     */
    virtual void setTimeout(int msecs);

signals:
    /**
     * @brief This signal is emitted when a new request is available.
     *
     * @param req The incoming request
     * @param res The outgoing response
     */
    void newRequest(Request req, Response* res);

    /**
     * @brief This signal is emitted when the socket disconnects.
     */
    void disconnected();

    /**
     * @brief This signal is emitted when the timeout has changed.
     */
    void timeoutChanged();

protected:
    /**
     * @brief Contructs a new connection.
     */
    explicit Connection(QObject* parent = nullptr);

private:
    int m_timeout = 0;
};

FLUGS_END_NAMESPACE

#endif
