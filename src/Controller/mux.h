/****************************************************************************
**
** This file is part of Flugs.
**
** Copyright 2017 Stefan Böhmann <sboehmann@flugs.io>
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
#ifndef FLUGS_CONTROLLER_MUX_H
#define FLUGS_CONTROLLER_MUX_H

#include "flugs_controller_export.h"
#include <Flugs/Controller/Controller>
#include <Flugs/Foundation/Server>
#include <Flugs/Router/Router>

FLUGS_BEGIN_NAMESPACE

typedef Route& (Router::*RouterAddFn)(const QString&, HandlerFunction);

class FLUGS_CONTROLLER_EXPORT Mux : public QObject
{
    Q_OBJECT

public:
    explicit Mux(QObject* parent = nullptr);
    explicit Mux(Server* server, QObject* parent = nullptr);
    virtual ~Mux();

    void serve(Server* server);

    void addController(Controller* ctrl);
    void removeController(Controller* ctrl);

protected:
    bool registerControllerMethodByName(const QString& className, const QString& methodName, const QMetaMethod& method, QVector<RouterAddFn> handlers);

private:
    Router m_router;
};

FLUGS_END_NAMESPACE

#endif
