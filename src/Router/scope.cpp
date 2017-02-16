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
#include "scope.h"
#include "scope_p.h"

FLUGS_USE_NAMESPACE

Scope::Scope(QObject* parent)
    : Middleware(parent)
    , d_ptr(new ScopePrivate(this))
{
}

Scope::Scope(ScopePrivate& dd, QObject* parent)
    : Middleware(parent)
    , d_ptr(&dd)
{
}

Scope::~Scope()
{
}

Route& Scope::add(Route* r)
{
    Q_ASSERT(r);
    r->setParent(this);
    d_func()->routes.append(r);

    return *r;
}

Route& Scope::add(const QSet<Method::Type> methods, const QString& path, HandlerFunction handler)
{
    return add(new Route(methods, path, handler, this));
}

Route& Scope::add(Method::Type method, const QString& path, HandlerFunction handler)
{
    return add(new Route(method, path, handler, this));
}

Scope& Scope::subScope()
{
    Q_D(Scope);

    Scope* s = new Scope(this);
    s->setNextMiddleware([&](Request& req, Response* res) { next(req, res); });

    if(d->lastScope) {
        d->lastScope->setNextMiddleware(s);
    }
    d->lastScope = s;

    if(!d->scope) {
        d->scope = s;
    }

    return *s;
}

Scope& Scope::pathPrefix(const QString& pathPrefix, Qt::CaseSensitivity cs)
{
    d_func()->pathPrefix = pathPrefix;
    d_func()->pathPrefixCaseSensitivity = cs;

    return *this;
}

Scope& Scope::host(const QString& host)
{
    d_func()->host = host.trimmed();
    return *this;
}

Scope& Scope::use(Middleware* m)
{
    Q_ASSERT(m);
    Q_D(Scope);

    if(d->lastMiddleware) {
        d->lastMiddleware->setNextMiddleware(m);
    }
    d->lastMiddleware = m;
    m->setNextMiddleware(this);

    if(!d->middleware) {
        d->middleware = m;
    }

    return *this;
}

void Scope::handleRequest(Request req, Response* res)
{
    Q_D(Scope);

    if (d->middleware) {
        d->middleware->handle(req, res);
    }
    else {
        handle(req, res);
    }
}

void Scope::handle(Request req, Response* res)
{
    Q_D(Scope);

    QUrl url = req.url();

    if (!d->host.isEmpty()) {
        if (url.host(QUrl::EncodeUnicode).compare(d->host, Qt::CaseInsensitive) != 0) {
            next(req, res);
            return;
        }
    }

    if (!d->pathPrefix.isEmpty()) {
        // FIXME parse params and add them to the request params

        if (!url.path().startsWith(d->pathPrefix, d->pathPrefixCaseSensitivity)) {
            next(req, res);
            return;
        }

        url.setPath(url.path().remove(0, d->pathPrefix.size()));
    }

    foreach (Route* r, d->routes) {
        Request request(req);
        if (r->handlerFunc() && r->match(request)) {
            r->handlerFunc()(request, res);
            return;
        }
    }

    if (d->scope) {
        d->scope->handleRequest(req, res);
    }
}
