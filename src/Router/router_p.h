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
#ifndef FLUGS_ROUTER_PRIVATE_H
#define FLUGS_ROUTER_PRIVATE_H

#include "router.h"
#include "scope_p.h"
#include "server.h"

FLUGS_BEGIN_NAMESPACE

class RouterPrivate : public ScopePrivate
{
    Q_DECLARE_PUBLIC(Router)

public:
    virtual ~RouterPrivate()
    {
    }

protected:
    explicit RouterPrivate(Router* q)
        : ScopePrivate(q)
    {
    }

    Server* server = nullptr;

    bool redirectTrailingSlashEnabled = true;
    bool defaultMethodNotAllowedHandlerEnabled = true;
    bool defaultOptionsHandlerEnabled = true;

    HandlerFunction notFoundHandler = nullptr;
    HandlerFunction methodNotAllowedHandler = nullptr;
    HandlerFunction internalServerErrorHandler = nullptr;
};

FLUGS_END_NAMESPACE

#endif
