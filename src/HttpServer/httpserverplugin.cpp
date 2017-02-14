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
#include "httpserverplugin.h"

#include "httpserver.h"
#include "request.h"
#include "response.h"

#include <QtQml/QQmlEngine>

FLUGS_USE_NAMESPACE

void HttpServerPlugin::registerTypes(const char* uri)
{
    qmlRegisterType<FLUGS_NAMESPACE_PREFIX HttpServer>(uri, 1, 0, "HttpServer");
    qmlRegisterUncreatableType<FLUGS_NAMESPACE_PREFIX Request>(uri, 1, 0, "Request", QStringLiteral(""));
    qmlRegisterUncreatableType<FLUGS_NAMESPACE_PREFIX Response>(uri, 1, 0, "Response", QStringLiteral(""));
}
