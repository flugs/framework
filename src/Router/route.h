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
#ifndef FLUGS_ROUTER_ROUTE_H
#define FLUGS_ROUTER_ROUTE_H

#include "flugs_router_export.h"
#include <Flugs/Foundation/Middleware>
#include <Flugs/Router/RouteBuilder>

#include <QScopedPointer>

FLUGS_BEGIN_NAMESPACE

class Scope;
class Request;
class Response;

using HandlerFunction = std::function<void(Request, Response*)>;

class RoutePrivate;

class FLUGS_ROUTER_EXPORT Route : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Route)

public:
    using Builder = RouteBuilder;

    enum MatchState {
        Ok,
        MethodError,
        PathSizeError,
        PathError,
        PathRegExError
    };

    explicit Route(QObject* parent = nullptr);
    virtual ~Route();

    Route& name(const QString& name);
    Route& methods(Method::Types methods);
    Route& path(const QString& path);
    Route& handler(HandlerFunction handler);
    Route& use(Middleware* m);

    HandlerFunction handlerFunc();

    static Builder to(const QString &name);

protected:
    friend class Scope;

    explicit Route(Method::Types methods, const QString& path, HandlerFunction handler, QObject* parent = nullptr);
    explicit Route(RoutePrivate& dd, QObject* parent = nullptr);

    MatchState match(Request& req);

    static MatchState parsePathSegment(const QString &requestPathSeg, const QString &matchPathSeg, Request &req);
    static MatchState parsePath(const QString &requestPath, const QString &matchPath, Request &req);

private:
    Q_DECLARE_PRIVATE(Route)
    QScopedPointer<RoutePrivate> d_ptr;
};

FLUGS_END_NAMESPACE

#endif
