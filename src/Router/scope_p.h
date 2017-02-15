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
#ifndef FLUGS_SCOPE_PRIVATE_H
#define FLUGS_SCOPE_PRIVATE_H

#include "flugs_router_export.h"

#include <Flugs/Foundation/Global>
#include <Flugs/Router/Scope>

FLUGS_BEGIN_NAMESPACE

class ScopePrivate
{
    Q_DECLARE_PUBLIC(Scope)

public:
    virtual ~ScopePrivate()
    {
    }

protected:
    explicit ScopePrivate(Scope* q)
        : q_ptr(q)
    {
    }

    Scope* const q_ptr = nullptr;

    QString pathPrefix;
    Qt::CaseSensitivity pathPrefixCaseSensitivity = Qt::CaseSensitive;
    QString host;
    Middleware* middleware = nullptr;
    Scope* scope = nullptr;
    Scope* lastScope = nullptr;
    QList<Route*> routes;
};

FLUGS_END_NAMESPACE

#endif
