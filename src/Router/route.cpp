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

#include <QRegularExpression>

FLUGS_USE_NAMESPACE

Route::Route(QObject* parent)
    : QObject(parent)
    , d_ptr(new RoutePrivate(this))
{
}

Route::Route(Method::Types methods, const QString& path, HandlerFunction handler, QObject* parent)
    : QObject(parent)
    , d_ptr(new RoutePrivate(this))
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
}

Route::~Route()
{
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


Route::MatchState Route::parsePath(const QString &requestPath, const QString &matchPath, Request &req)
{
    const QStringList mpath = matchPath.split(QChar::fromLatin1('/'));
    const QStringList rpath = requestPath.split(QChar::fromLatin1('/'));

    if (mpath.size() != rpath.size()) {
        return Route::PathError;
    }

    for (int i = 0; i < mpath.size(); ++i) {
        const QString mp = mpath.at(i);
        const QString rp = rpath.at(i);

        if (mp.startsWith(QChar::fromLatin1(':'))) {
            // variable path segment...
            req.addPathParam(mp.mid(1), rp);
        }
        else if (mp.startsWith(QChar::fromLatin1('{')) && mp.endsWith(QChar::fromLatin1('}'))) {
            // advanved variable path segment...
            QString p = mp.mid(1, mp.length() - 2);

            if (!p.contains(QChar::fromLatin1(':'))) {
                req.addPathParam(p, rp);
            }
            else {
                QString key = p.mid(0, p.indexOf(QChar::fromLatin1(':')));
                QString pattern = p.mid(p.indexOf(QChar::fromLatin1(':')) + 1);

                QRegularExpression re(pattern);
                if (re.match(rp).hasMatch()) {
                    req.addPathParam(key, rp);
                }
                else {
                    return Route::PathRegExError;
                }
            }
        }
        else if (mp != rp) {
            return Route::PathError;
        }
    }

    return Route::Ok;
}
