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
#ifndef FLUGS_FOUNDATION_REQUEST_H
#define FLUGS_FOUNDATION_REQUEST_H

#include <Flugs/Foundation/Header>
#include <Flugs/Foundation/Headers>
#include <Flugs/Foundation/Method>
#include <QSharedDataPointer>

FLUGS_BEGIN_NAMESPACE

struct RequestData;

/**
 * The Request class represents the header and body data sent by the client.
 * The class is <b>read-only</b>.
 * @sa Connection
 */
class FLUGS_FOUNDATION_EXPORT Request
{
    Q_GADGET

public:
    Request();
    Request(const Request& other);
    Request& operator=(const Request& other);
    ~Request();

    void clear();

    bool containsParam(const QString& name) const;
    QString param(const QString& name, const QString& defaultValue = QString()) const;

    bool containsPathParam(const QString& name) const;
    QString pathParam(const QString& name, const QString& defaultValue = QString()) const;
    void addPathParam(const QString& name, const QString& value);

    bool containsFormParam(const QString& name) const;
    QString formParam(const QString& name, const QString& defaultValue = QString()) const;
    void addFormParam(const QString& name, const QString& value);

    bool containsQueryParam(const QString& name) const;
    QString queryParam(const QString& name, const QString& defaultValue = QString()) const;
    void addQueryParam(const QString& name, const QString& value);

    Headers headers() const;
    Header header(const QByteArray& name, const Header& defaultValue = Header()) const;
    Header header(Header::Name name, const Header& defaultValue = Header()) const;
    void setHeaders(const Headers& headers);
    void addHeader(const QByteArray& key, const QByteArray& value);
    void addHeader(Header::Name name, const QByteArray& value);

    /**
     * The HTTP version of the packet.
     */
    QVersionNumber httpVersion() const;
    void setHttpVersion(const QVersionNumber& version);

    /**
     * returns the collected body requested by collectData().
     */
    QByteArray body() const;
    void setBody(const QByteArray& body);
    void appendBody(const QByteArray& body);

    /**
     * The method used for the request.
     */
    Method method() const;
    void setMethod(const Method& method);
    void setMethod(Method::Type type);

    /**
     * The complete URL for the request.
     * This includes the path and query string. @sa path().
     */
    QUrl url() const;
    void setUrl(const QUrl& url);

    /**
     * IP Address of the client in dotted decimal format.
     */
    QHostAddress remoteAddress() const;
    void setRemoteAddress(const QHostAddress& remoteAddress);

    /**
     * Outbound connection port for the client.
     */
    quint16 remotePort() const;
    void setRemotePort(quint16 remotePort);

protected:
    QSharedDataPointer<RequestData> d;
};

FLUGS_END_NAMESPACE

#endif
