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
#ifndef FLUGS_FOUNDATION_SERVER_H
#define FLUGS_FOUNDATION_SERVER_H

#include <Flugs/Foundation/Global>

FLUGS_BEGIN_NAMESPACE

class Connection;
class Request;
class Response;

/**
 * @brief
 */
class FLUGS_FOUNDATION_EXPORT Server : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Server)

    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)

public:
    /**
     * @brief Constructs a Flugs object.
     *
     * @param parent is passed to the QObject constructor.
     */
    explicit Server(QObject* parent = nullptr);

    /**
     * @brief Destroys the Flugs object.
     * If the server is listening for connections, the socket is automatically closed.
     */
    virtual ~Server();

    /**
     * @brief Returns true if the server is currently listening for incoming connections; otherwise returns false.
     */
    virtual bool isListening() const = 0;

    /**
     * @brief Closes the server and stops from listening.
     */
    virtual void close() = 0;

    /**
     * @brief Returns timeout value in milliseconds
     * @see setTimeout().
     */
    int timeout() const;

    /**
     *
     */
    virtual QAbstractSocket::SocketError serverError() const = 0;

    /**
     *
     */
    virtual QString errorString() const = 0;

public slots:
    /**
     * @brief Set the timeout for new connections in miliseconds.
     * @see timeout().
     */
    virtual void setTimeout(int value);

signals:
    /**
     * @brief This signal is emitted when accepting a new connection results in an error.
     */
    void acceptError(QAbstractSocket::SocketError socketError);

    /**
     * @brief This signal is emitted when a client makes a new request to the server.
     */
    void newRequest(Request request, Response* response);

    /**
     * @brief This signal is emitted every time a new connection is available.
     */
    void newConnection(Connection* connection);

    /**
     * @brief This signal is emitted when the timeout has changed.
     */
    void timeoutChanged();

private:
    int m_timeout = 0;
};

FLUGS_END_NAMESPACE

#endif
