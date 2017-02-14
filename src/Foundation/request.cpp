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
#include "request.h"
#include <QSharedData>

FLUGS_BEGIN_NAMESPACE

struct RequestData : public QSharedData
{
    RequestData()
    {
    }

    RequestData(const RequestData& other)
        : QSharedData(other)
        , body(other.body)
        , headers(other.headers)
        , httpVersion(other.httpVersion)
        , method(other.method)
        , url(other.url)
        , remoteAddress(other.remoteAddress)
        , remotePort(other.remotePort)
    {
    }

    ~RequestData()
    {
    }

    QByteArray body;
    Headers headers;
    QVersionNumber httpVersion;
    Method method;
    QUrl url;
    QHostAddress remoteAddress;
    QHash<QString, QString> pathParams;
    QHash<QString, QString> formParams;
    QHash<QString, QString> queryParams;
    quint16 remotePort = 0;
};

Request::Request()
    : d(new RequestData)
{
}

Request::Request(const Request& other)
    : d(other.d)
{
}

Request& Request::operator=(const Request& other)
{
    d = other.d;
    return *this;
}

Request::~Request()
{
}

void Request::clear()
{
    // FIXME must be faster
    d = new RequestData;
}

bool Request::containsParam(const QString& name) const
{
    // FIXME handle not only path parameters
    return containsPathParam(name) || containsFormParam(name);
}

QString Request::param(const QString& name, const QString& defaultValue) const
{
    if (containsPathParam(name)) {
        return pathParam(name);
    }
    else if (containsQueryParam(name)) {
        return queryParam(name);
    }
    else if (containsFormParam(name)) {
        return formParam(name);
    }

    return defaultValue;
}

bool Request::containsPathParam(const QString& name) const
{
    return d->pathParams.contains(name);
}

QString Request::pathParam(const QString& name, const QString& defaultValue) const
{
    return d->pathParams.value(name, defaultValue);
}

void Request::addPathParam(const QString& name, const QString& value)
{
    d->pathParams.insert(name, value);
}

bool Request::containsFormParam(const QString& name) const
{
    return d->formParams.contains(name);
}

QString Request::formParam(const QString& name, const QString& defaultValue) const
{
    return d->formParams.value(name, defaultValue);
}

void Request::addFormParam(const QString& name, const QString& value)
{
    d->formParams.insert(name, value);
}

bool Request::containsQueryParam(const QString& name) const
{
    return d->queryParams.contains(name);
}

QString Request::queryParam(const QString& name, const QString& defaultValue) const
{
    return d->queryParams.value(name, defaultValue);
}

void Request::addQueryParam(const QString& name, const QString& value)
{
    d->queryParams.insert(name, value);
}

Headers Request::headers() const
{
    return d->headers;
}

Header Request::header(const QByteArray& name, const Header& defaultValue) const
{
    return d->headers.header(name, defaultValue);
}

Header Request::header(Header::Name name, const Header& defaultValue) const
{
    return d->headers.header(name, defaultValue);
}

void Request::setHeaders(const Headers& headers)
{
    d->headers = headers;
}

void Request::addHeader(const QByteArray& key, const QByteArray& value)
{
    d->headers.insert(key, value);
}

void Request::addHeader(Header::Name name, const QByteArray& value)
{
    d->headers.insert(name, value);
}

QVersionNumber Request::httpVersion() const
{
    return d->httpVersion;
}

void Request::setHttpVersion(const QVersionNumber& version)
{
    d->httpVersion = version;
}

QByteArray Request::body() const
{
    return d->body;
}

void Request::setBody(const QByteArray& body)
{
    d->body = body;
}

void Request::appendBody(const QByteArray& body)
{
    d->body.append(body);
}

Method Request::method() const
{
    return d->method;
}

void Request::setMethod(const Method& method)
{
    d->method = method;
}

void Request::setMethod(Method::Type type)
{
    setMethod(Method(type));
}

QUrl Request::url() const
{
    return d->url;
}

void Request::setUrl(const QUrl& url)
{
    d->url = url;
}

QHostAddress Request::remoteAddress() const
{
    return d->remoteAddress;
}

void Request::setRemoteAddress(const QHostAddress& remoteAddress)
{
    d->remoteAddress = remoteAddress;
}

quint16 Request::remotePort() const
{
    return d->remotePort;
}

void Request::setRemotePort(quint16 remotePort)
{
    d->remotePort = remotePort;
}

FLUGS_END_NAMESPACE
