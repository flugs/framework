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
#ifndef FLUGS_ROUTER_ROUTE_PRIVATE_H
#define FLUGS_ROUTER_ROUTE_PRIVATE_H

#include "route.h"

FLUGS_BEGIN_NAMESPACE

class FLUGS_ROUTER_EXPORT RoutePrivate
{
    Q_DISABLE_COPY(RoutePrivate)

public:
    explicit RoutePrivate(Route* qq)
        : q_ptr(qq)
    {
    }

    virtual ~RoutePrivate()
    {
    }

    QString name;
    QString path;
    QSet<Method::Type> methods;
    QList<Middleware*> middleware;
    HandlerFunction handler = nullptr;

protected:
    Route* const q_ptr;
};

FLUGS_END_NAMESPACE

#endif
