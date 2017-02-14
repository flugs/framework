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
#ifndef FLUGS_FOUNDATION_MIDDLEWARE_H
#define FLUGS_FOUNDATION_MIDDLEWARE_H

#include <Flugs/Foundation/Request>
#include <Flugs/Foundation/Response>

FLUGS_BEGIN_NAMESPACE

class Scope;

/**
 * @brief The Middleware class
 */
class FLUGS_FOUNDATION_EXPORT Middleware : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Middleware)

    friend class Scope;

public:
    explicit Middleware(QObject* parent = nullptr);
    virtual ~Middleware();

protected:
    virtual void handle(Request req, Response* res) = 0;

    virtual void terminate(const Request& req, const Response* res);

    void next(Request req, Response* res)
    {
        if (m_nextMiddleware) {
            m_nextMiddleware->handle(req, res);
        }
        else if (m_nextMiddlewareFunc) {
            m_nextMiddlewareFunc(req, res);
        }
    }

    Middleware* nextMiddleware()
    {
        return m_nextMiddleware;
    }

    void setNextMiddleware(Middleware* middleware)
    {
        m_nextMiddleware = middleware;
        m_nextMiddlewareFunc = nullptr;
    }

    void setNextMiddleware(std::function<void(Request&, Response*)> middlewareFunc)
    {
        m_nextMiddlewareFunc = middlewareFunc;
        m_nextMiddleware = nullptr;
    }

private:
    Middleware* m_nextMiddleware = nullptr;
    std::function<void(Request&, Response*)> m_nextMiddlewareFunc = nullptr;
};

FLUGS_END_NAMESPACE

#endif
