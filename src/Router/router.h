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
#ifndef FLUGS_ROUTER_H
#define FLUGS_ROUTER_H

#include <Flugs/Foundation/Server>
#include <Flugs/Router/Scope>

FLUGS_BEGIN_NAMESPACE

class RouterPrivate;

class FLUGS_ROUTER_EXPORT Router : public Scope
{
    Q_OBJECT
    Q_PROPERTY(bool redirectTrailingSlashEnabled READ redirectTrailingSlashEnabled WRITE setRedirectTrailingSlashEnabled NOTIFY redirectTrailingSlashEnabledChanged)
    Q_PROPERTY(bool defaultMethodNotAllowedHandlerEnabled READ defaultMethodNotAllowedHandlerEnabled WRITE setDefaultMethodNotAllowedHandlerEnabled NOTIFY defaultMethodNotAllowedHandlerEnabledChanged)
    Q_PROPERTY(bool defaultOptionsHandlerEnabled READ defaultOptionsHandlerEnabled WRITE setDefaultOptionsHandlerEnabled NOTIFY defaultOptionsHandlerEnabledChanged)

public:
    explicit Router(QObject *parent = nullptr);
    explicit Router(Server* server, QObject *parent = nullptr);
    virtual ~Router();

    void serve(Server* server);

    /**
     * @brief Handler which is called when no matching route is found.
     * @param handler
     */
    HandlerFunction notFoundHandler() const;
    void setNotFoundHandler(HandlerFunction handler);

    /**
     * @brief Handler which is called when a request cannot be routed and HandleMethodNotAllowed is true.
     * The "Allow" header with allowed request methods is set before the handler is called.
     */
    HandlerFunction methodNotAllowedHandler() const;
    void setMethodNotAllowedHandler(HandlerFunction handler);

    /**
     *
     */
    HandlerFunction internalServerErrorHandler() const;
    void setInternalServerErrorHandler(HandlerFunction handler);

    /**
     * Enables automatic redirection if the current route can't be matched but a handler for
     * the path with (without) the trailing slash exists.
     * For example if /foo/ is requested but a route only exists for /foo, the client is
     * redirected to /foo with http status code 301 for GET requests and 307 for all
     * other request methods.
     */
    bool redirectTrailingSlashEnabled() const;

    /**
     * If enabled, the router checks if another method is allowed for the current route, if the
     * current request can not be routed. If this is the case, the request is answered with
     * 'Method Not Allowed' and HTTP status code 405.
     * If no other Method is allowed, the request is delegated to the NotFound handler.
     */
    bool defaultMethodNotAllowedHandlerEnabled() const;

    /**
     * If enabled, the router automatically replies to OPTIONS requests.
     * Custom OPTIONS handlers take priority over automatic replies.
     */
    bool defaultOptionsHandlerEnabled() const;

public slots:
    void setRedirectTrailingSlashEnabled(bool state);
    void setDefaultMethodNotAllowedHandlerEnabled(bool state);
    void setDefaultOptionsHandlerEnabled(bool state);

signals:
    void redirectTrailingSlashEnabledChanged();
    void defaultMethodNotAllowedHandlerEnabledChanged();
    void defaultOptionsHandlerEnabledChanged();

protected:
    void handle(Request req, Response* res) override;

private:
    Q_DECLARE_PRIVATE(Router)
};

FLUGS_END_NAMESPACE

#endif
