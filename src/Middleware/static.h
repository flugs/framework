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
#ifndef FLUGS_MIDDLEWARE_STATIC_H
#define FLUGS_MIDDLEWARE_STATIC_H

#include <Flugs/Foundation/Middleware>

#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>

FLUGS_BEGIN_NAMESPACE

class Static : public Middleware
{
    Q_OBJECT

public:
    explicit Static(QObject* parent = nullptr);
    explicit Static(const QString& path, QObject* parent = nullptr);
    explicit Static(const QString& path, const QString& prefix, QObject* parent = nullptr);

    QString path() const
    {
        return m_path;
    }

    void setPath(const QString& path)
    {
        m_path = path;
    }

    QString prefix() const
    {
        return m_prefix;
    }

    void setPrefix(const QString& prefix)
    {
        m_prefix = prefix;
    }

    QString indexFile() const
    {
        return m_indexFile;
    }

    void setIndexFile(const QString& fileName)
    {
        m_indexFile = fileName;
    }

protected:
    void handle(Request request, Response* response) override;

private:
    QString m_path;
    QString m_prefix;
    QString m_indexFile;
};

FLUGS_END_NAMESPACE

#endif
