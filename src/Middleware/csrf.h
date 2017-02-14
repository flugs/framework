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
#ifndef FLUGS_MIDDLEWARE_CSRF_H
#define FLUGS_MIDDLEWARE_CSRF_H

#include <Flugs/Foundation/Middleware>

FLUGS_BEGIN_NAMESPACE

class CSRF : public Middleware
{
    Q_OBJECT

protected:
    void handle(Request request, Response* response) override
    {
        next(request, response);
    }
};

FLUGS_END_NAMESPACE

#endif
