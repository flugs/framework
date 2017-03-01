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
#include "routebuilder.h"
#include <Flugs/Router/Route>

#include <QPointer>

FLUGS_USE_NAMESPACE

struct RoutePrivate
{
    explicit RoutePrivate(Route *r)
      : route(r)
    {
        if(!route.isNull()) {
            path = route->path();
        }
    }

    QString path;
    QPointer<Route> route;
};


RouteBuilder::RouteBuilder(QList<Route*> route)
{
    foreach(Route *r, route) {
        m_list.append(new RoutePrivate(r));
    }
}

RouteBuilder::~RouteBuilder()
{
    qDeleteAll(m_list);
}

bool RouteBuilder::isValid() const
{
}

RouteBuilder& RouteBuilder::arg(const QString &value)
{
}

RouteBuilder& RouteBuilder::param(const QString &key, const QString &value)
{

}

QUrl RouteBuilder::url() const
{
    if(!isValid()) {
        return QUrl();
    }

    return QUrl();
}
