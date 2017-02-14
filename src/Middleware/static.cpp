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
#include "static.h"

#include <Flugs/Foundation/Header>
#include <Flugs/Foundation/Method>

FLUGS_USE_NAMESPACE

Static::Static(QObject* parent)
    : Static(QStringLiteral("/public"), QString(), parent)
{
}

Static::Static(const QString& path, QObject* parent)
    : Static(path, QString(), parent)
{
}

Static::Static(const QString& path, const QString& prefix, QObject* parent)
    : Middleware(parent)
    , m_path(path)
    , m_prefix(prefix)
{
}

void Static::handle(Request request, Response* response)
{
    if (request.method() != Method::Get && request.method() != Method::Head) {
        next(request, response);
        return;
    }

    QString file = request.url().path();
    if (!m_prefix.isEmpty()) {
        if (!file.startsWith(m_prefix)) {
            next(request, response);
            return;
        }

        file = file.mid(m_prefix.size());
        if (!file.isEmpty() && !file.startsWith(QLatin1Char('/'))) {
            next(request, response);
            return;
        }
    }

    QFileInfo info(m_path + QLatin1Char('/') + file);

    // check if it exists, is readable and is in a subdirectory of m_path
    if (!info.exists() || info.absoluteFilePath().startsWith(m_path)) {
        next(request, response);
        return;
    }

    if (info.isDir()) {
        // redirect in missing trailing slash
        if (!file.endsWith(QLatin1Char('/'))) {
            QUrl url = request.url();
            url.setPath(url.path() + QLatin1Char('/'));
            response->redirect(url);
            return;
        }

        info.setFile(m_indexFile);
    }

    if (info.isFile()) {
        // TODO Use Last-Modified and If-Modified-Since header
        // TODO Handle ETag, If-Range and If-Not-Match

        if (!response->writeFile(info)) {
            response->forbidden();
        }
    }
    else {
        next(request, response);
    }
}
