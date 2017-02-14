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
#include "response.h"
#include <QMimeDatabase>
#include <QMimeType>

FLUGS_USE_NAMESPACE

Response::Response(QObject* parent)
    : QObject(parent)
{
}

Response::~Response()
{
}

qint64 Response::write(QIODevice* dev)
{
    if (!dev) {
        return -1;
    }

    char buf[4096];
    qint64 pos = 0;
    while ((pos = dev->read(buf, sizeof(buf))) != -1) {
        write(buf, pos);
    }

    return pos;
}

bool Response::writeFile(const QFileInfo& fileInfo, const QMimeType& mimeType)
{
    QMimeType mt = mimeType;
    if (!mt.isValid()) {
        QMimeDatabase db;
        mt = db.mimeTypeForFile(fileInfo);
    }

    QFile file(fileInfo.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    headers().setContentType(mt.name());
    write(&file);
    file.close();
    return true;
}

void Response::setStatusCode(Status::Code code)
{
    setStatus(Status(code));
}
