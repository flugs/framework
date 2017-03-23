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
#ifndef FLUGS_ROUTER_ROUTE_BUILDER_H
#define FLUGS_ROUTER_ROUTE_BUILDER_H

#include "flugs_router_export.h"
#include <Flugs/Foundation/Global>

#include <QtCore/QList>

FLUGS_BEGIN_NAMESPACE

class Route;

class FLUGS_ROUTER_EXPORT RouteBuilder
{
public:
    explicit RouteBuilder(QList<Route*> route);
    ~RouteBuilder();

    bool isValid() const;

    RouteBuilder& arg(const QVariant &value);
    RouteBuilder& param(const QString &key, const QVariant &value);

    QUrl url() const;

private:
    QHash<QString, QPointer<Route>> m_routes;
};

FLUGS_END_NAMESPACE

#endif
