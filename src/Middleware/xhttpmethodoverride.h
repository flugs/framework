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
#ifndef FLUGS_MIDDLEWARE_XHTTPMETHODOVERRIDE_H
#define FLUGS_MIDDLEWARE_XHTTPMETHODOVERRIDE_H

#include <Flugs/Foundation/Middleware>

FLUGS_BEGIN_NAMESPACE

/**
* @brief X-HTTP-Method-Override middleware
*
* XHttpMethodOverride checks the incoming request for the X-HTTP-Method-Override
* header and the parameter formParamName() (default is _method) in form or query data.
* Given the current request has been sent via POST, it uses the queried http method
* rather than the actual Request::method() for the following processing.
* These methods can be replaced: PUT, PATCH, DELETE.
* The methods PUT, PATCH and DELETE can so be replaced by POST requests.
*
* This is particularly useful for clients who have to endure a crazy and stupid
* system administrator.
*/
class XHttpMethodOverride : public Middleware
{
    Q_OBJECT

public:
    explicit XHttpMethodOverride(QObject* parent = nullptr);
    explicit XHttpMethodOverride(const QString& formParamName, QObject* parent = nullptr);

    QString formParamName() const
    {
        return m_formParamName;
    }

    void setFormParamName(const QString& name)
    {
        m_formParamName = name;
    }

protected:
    void handle(Request request, Response* response) override;

private:
    QString m_formParamName;
};

FLUGS_END_NAMESPACE

#endif
