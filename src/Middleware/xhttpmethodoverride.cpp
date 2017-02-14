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
#include "xhttpmethodoverride.h"

#include <Flugs/Foundation/Header>
#include <Flugs/Foundation/Method>

FLUGS_USE_NAMESPACE

XHttpMethodOverride::XHttpMethodOverride(QObject* parent)
    : XHttpMethodOverride(QStringLiteral("_method"), parent)
{
}

XHttpMethodOverride::XHttpMethodOverride(const QString& formParamName, QObject* parent)
    : Middleware(parent)
    , m_formParamName(formParamName)
{
}

void XHttpMethodOverride::handle(Request request, Response* response)
{
    static QSet<QString> methods({ QStringLiteral("PUT"), QStringLiteral("PATH"), QStringLiteral("DELETE") });

    if (request.method() == Method::Post) {
        QString m;
        if (request.containsQueryParam(m_formParamName)) {
            m = request.queryParam(m_formParamName).toUpper().trimmed();
        }
        else {
            m = request.formParam(m_formParamName).toUpper().trimmed();
        }

        if (!m.isEmpty() && !m_formParamName.isEmpty() && methods.contains(m)) {
            request.addHeader(Header::XHttpMethodOverride, m.toLatin1());
        }

        Header h = request.header(Header::XHttpMethodOverride);
        if (h.isValid()) {
            const QByteArray name = h.name().trimmed().toUpper();
            if (name == QByteArrayLiteral("PUT")) {
                request.setMethod(Method::Put);
            }
            else if (name == QByteArrayLiteral("PATCH")) {
                request.setMethod(Method::Patch);
            }
            else if (name == QByteArrayLiteral("DELETE")) {
                request.setMethod(Method::Delete);
            }
        }
    }

    next(request, response);
}
