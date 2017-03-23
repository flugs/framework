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
#include "route.h"
#include "route_p.h"

#include <QHash>
#include <QPointer>
#include <QRegularExpression>

FLUGS_USE_NAMESPACE

static QList<QPointer<FLUGS_NAMESPACE_PREFIX Route>> routeMap;


Route::Route(QObject* parent)
    : QObject(parent)
    , d_ptr(new RoutePrivate(this))
{
    routeMap.append(this);
}

Route::Route(Method::Types methods, const QString& path, HandlerFunction handler, QObject* parent)
    : Route(parent)
{
    Q_D(Route);

    d->methods = methods;
    d->path = path;
    d->handler = handler;
}

Route::Route(RoutePrivate& dd, QObject* parent)
    : QObject(parent)
    , d_ptr(&dd)
{
    routeMap.append(this);
}

Route::~Route()
{
    routeMap.removeOne(this);
}

Route& Route::name(const QString& name)
{
    d_func()->name = name.trimmed();
    return *this;
}

Route& Route::methods(Method::Types methods)
{
    d_func()->methods = methods;
    return *this;
}

Route& Route::path(const QString& path)
{
    d_func()->path = path;
    return *this;
}

Route& Route::handler(HandlerFunction handler)
{
    d_func()->handler = handler;
    return *this;
}

Route& Route::use(Middleware* m)
{
    d_func()->middleware.append(m);
    return *this;
}

QString Route::getPath() const
{
    return d_func()->path;
}

HandlerFunction Route::handlerFunc()
{
    return d_func()->handler;
}

Route::MatchState Route::match(Request& req)
{
    Q_D(Route);

    const auto state = parsePath(d->path, req.url().path(), req);
    if(state != Route::Ok) {
        return state;
    }

    if (!d->methods.testFlag(req.method().type())) {
        return Route::MethodError;
    }

    return Route::Ok;
}

Route::MatchState Route::parsePathSegment(const QString &requestPathSeg, const QString &matchPathSeg, Request &req)
{
    if (matchPathSeg.startsWith(QChar::fromLatin1(':'))) {
        // variable path segment...
        req.addPathParam(matchPathSeg.mid(1), requestPathSeg);
    }
    else if (matchPathSeg.startsWith(QChar::fromLatin1('{')) && matchPathSeg.endsWith(QChar::fromLatin1('}'))) {
        // advanved variable path segment...
        QString p = matchPathSeg.mid(1, matchPathSeg.length() - 2);

        if (!p.contains(QChar::fromLatin1(':'))) {
            req.addPathParam(p, requestPathSeg);
        }
        else {
            QString key = p.mid(0, p.indexOf(QChar::fromLatin1(':')));
            QString pattern = p.mid(p.indexOf(QChar::fromLatin1(':')) + 1);

            QRegularExpression re(pattern);
            if (re.match(requestPathSeg).hasMatch()) {
                req.addPathParam(key, requestPathSeg);
            }
            else {
                return Route::PathRegExError;
            }
        }
    }
    else if (matchPathSeg != requestPathSeg) {
        return Route::PathError;
    }

    return Route::Ok;
}

Route::MatchState Route::parsePath(const QString &requestPath, const QString &matchPath, Request &req)
{
    const QStringList mpath = matchPath.split(QChar::fromLatin1('/'));
    const QStringList rpath = requestPath.split(QChar::fromLatin1('/'));

    if (mpath.size() != rpath.size()) {
        return Route::PathError;
    }

    Route::MatchState state = Route::Ok;
    for (int i = 0; i < mpath.size(); ++i) {
        state = parsePathSegment(rpath.at(i), mpath.at(i), req);
        if(state != Route::Ok) {
            break;
        }
    }

    return state;
}

Route::Builder Route::to(const QString &name)
{
    QList<Route*> list;
    foreach(const QPointer<Route> r, routeMap) {
        if(!r.isNull() && !r->d_func()->name.isEmpty() && r->d_func()->name == name) {
            list.append(r);
        }
    }

   return Route::Builder(list);
}

