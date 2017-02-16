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
#include "router.h"
#include "router_p.h"

FLUGS_USE_NAMESPACE

Router::Router(QObject *parent)
    : Router(nullptr, parent)
{
}

Router::Router(Server* server, QObject *parent)
    : Scope(*new RouterPrivate(this), parent)
{
    serve(server);
}

Router::~Router()
{
}

void Router::serve(Server* server)
{
    Q_D(Router);

    if (d->server) {
        d->server->disconnect(this);
        d->server = nullptr;
    }

    if (server) {
        d->server = server;
        connect(d->server, &Server::newRequest, this, &Router::handleRequest);
    }
}

HandlerFunction Router::notFoundHandler() const
{
    return d_func()->notFoundHandler;
}

void Router::setNotFoundHandler(HandlerFunction handler)
{
    d_func()->notFoundHandler = handler;
}

HandlerFunction Router::methodNotAllowedHandler() const
{
    return d_func()->methodNotAllowedHandler;
}

void Router::setMethodNotAllowedHandler(HandlerFunction handler)
{
    d_func()->methodNotAllowedHandler = handler;
}

HandlerFunction Router::internalServerErrorHandler() const
{
    return d_func()->internalServerErrorHandler;
}

void Router::setInternalServerErrorHandler(HandlerFunction handler)
{
    d_func()->internalServerErrorHandler = handler;
}

bool Router::redirectTrailingSlashEnabled() const
{
    return d_func()->redirectTrailingSlashEnabled;
}

void Router::setRedirectTrailingSlashEnabled(bool state)
{
    Q_D(Router);

    if (d->redirectTrailingSlashEnabled != state) {
        d->redirectTrailingSlashEnabled = state;
        emit redirectTrailingSlashEnabledChanged();
    }
}

bool Router::defaultMethodNotAllowedHandlerEnabled() const
{
    return d_func()->defaultMethodNotAllowedHandlerEnabled;
}

void Router::setDefaultMethodNotAllowedHandlerEnabled(bool state)
{
    Q_D(Router);

    if (d->defaultMethodNotAllowedHandlerEnabled != state) {
        d->defaultMethodNotAllowedHandlerEnabled = state;
        emit defaultMethodNotAllowedHandlerEnabledChanged();
    }
}

bool Router::defaultOptionsHandlerEnabled() const
{
    return d_func()->defaultOptionsHandlerEnabled;
}

void Router::setDefaultOptionsHandlerEnabled(bool state)
{
    Q_D(Router);

    if (d->defaultOptionsHandlerEnabled != state) {
        d->defaultOptionsHandlerEnabled = state;
        emit defaultOptionsHandlerEnabledChanged();
    }
}

void Router::handle(Request req, Response* res)
{
    Q_D(Router);

    Scope::handle(req, res);

    if(!res->isFinished()) {
        if(d->notFoundHandler) {
            d->notFoundHandler(req, res);
        }
        else {
            res->setStatusCode(Status::NotFound);
            res->end();
        }
    }
}
