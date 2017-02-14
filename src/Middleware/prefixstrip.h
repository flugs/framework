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
#ifndef FLUGS_MIDDLEWARE_PREFIXSTRIP_H
#define FLUGS_MIDDLEWARE_PREFIXSTRIP_H

#include <Flugs/Foundation/Middleware>

FLUGS_BEGIN_NAMESPACE

class PrefixStrip : public Middleware
{
    Q_OBJECT

public:
    explicit PrefixStrip(const QString& prefix, bool required = false, Qt::CaseSensitivity cs = Qt::CaseInsensitive)
        : m_prefix(prefix)
        , m_cs(cs)
        , m_required(required)
    {
    }

    QString prefix() const
    {
        return m_prefix;
    }

    void setPrefix(const QString& value)
    {
        m_prefix = value;
    }

    Qt::CaseSensitivity caseSensitivity() const
    {
        return m_cs;
    }

    void setCaseSensitivity(Qt::CaseSensitivity cs)
    {
        m_cs = cs;
    }

    bool prefixRequired() const
    {
        return m_required;
    }

    void setPrefixRequired(bool state)
    {
        m_required = state;
    }

protected:
    void handle(Request req, Response* res) override
    {
        if (!m_prefix.isEmpty()) {
            QString path = req.url().path();
            if (path.startsWith(m_prefix, m_cs)) {
                path.remove(0, m_prefix.size());
                req.url().setPath(path);
            }
            else if (m_required) {
                res->notFound();
            }
        }

        next(req, res);
    }

private:
    QString m_prefix;
    Qt::CaseSensitivity m_cs;
    bool m_required = false;
};

FLUGS_END_NAMESPACE

#endif
