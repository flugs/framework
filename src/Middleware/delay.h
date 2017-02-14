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
#ifndef FLUGS_MIDDLEWARE_DELAY_H
#define FLUGS_MIDDLEWARE_DELAY_H

#include <Flugs/Foundation/Middleware>

#include <QTimer>

FLUGS_BEGIN_NAMESPACE

/**
 * @brief Middleware for adding delays to your endpoint.
 * Intended to simulate latency for testing its effects on faster networks.
 */
class Delay : public Middleware
{
    Q_OBJECT

    explicit Delay(const QByteArray& headerKey = QByteArrayLiteral("X-Add-Delay"))
        : m_headerKey(headerKey)
    {
    }

    QByteArray headerKey() const
    {
        return m_headerKey;
    }

    void setHeaderKey(const QByteArray& key)
    {
        m_headerKey = key;
    }

protected:
    void handle(Request request, Response* response) override
    {
        int value = request.headers().header(m_headerKey).value().toInt();
        if (value > 0) {
            QTimer::singleShot(value, this, [=]() { next(request, response); });
        }
        else {
            next(request, response);
        }
    }

private:
    QByteArray m_headerKey;
};

FLUGS_END_NAMESPACE

#endif
