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
#ifndef FLUGS_SCOPE_H
#define FLUGS_SCOPE_H

#include "flugs_router_export.h"
#include <Flugs/Foundation/Method>
#include <Flugs/Foundation/Middleware>
#include <Flugs/Router/Route>

FLUGS_BEGIN_NAMESPACE

class ScopePrivate;

class FLUGS_ROUTER_EXPORT Scope : public Middleware
{
    Q_OBJECT
    Q_DISABLE_COPY(Scope)

public:
    virtual ~Scope();

    Scope& subScope();

    Route& add(Route* route);
    Route& add(const QSet<Method::Type> method, const QString& path, HandlerFunction handler);
    Route& add(Method::Type method, const QString& path, HandlerFunction handler);

    Scope& pathPrefix(const QString& pathPrefix, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    Scope& host(const QString& host);
    Scope& use(Middleware* middleware);

    Route& get(const QString& path, HandlerFunction handler)
    {
        return add(Method::Type::Get, path, handler);
    }

    Route& put(const QString& path, HandlerFunction handler)
    {
        return add(Method::Type::Get, path, handler);
    }

    Route& post(const QString& path, HandlerFunction handler)
    {
        return add(Method::Type::Get, path, handler);
    }

    Route& head(const QString& path, HandlerFunction handler)
    {
        return add(Method::Type::Get, path, handler);
    }

    Route& options(const QString& path, HandlerFunction handler)
    {
        return add(Method::Type::Get, path, handler);
    }

    Route& patch(const QString& path, HandlerFunction handler)
    {
        return add(Method::Type::Get, path, handler);
    }

    Route& del(const QString& path, HandlerFunction handler)
    {
        return add(Method::Type::Get, path, handler);
    }

protected:
    explicit Scope(QObject* parent = nullptr);
    explicit Scope(ScopePrivate& d, QObject* parent = nullptr);

    virtual void handleRequest(Request req, Response* res);
    void handle(Request req, Response* res) override;
    Route::MatchState matchState() const;

protected:
    Q_DECLARE_PRIVATE(Scope)
    QScopedPointer<ScopePrivate> d_ptr;
};

FLUGS_END_NAMESPACE

#endif
