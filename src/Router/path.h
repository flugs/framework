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
#ifndef FLUGS_PATH_H
#define FLUGS_PATH_H

#include "flugs_router_export.h"

#include <Flugs/Foundation/Global>

#include <QRegularExpression>

FLUGS_BEGIN_NAMESPACE


class Path
{
public:
    explicit Path(const QString &str);

    bool isEmpty() const
    {
        return !m_name.isEmpty();
    }

    bool isFixed()
    {
        return m_fixed;
    }

    bool isWildcard() const
    {
        return m_wildcard;
    }

    bool isOptional() const
    {
        return m_optional;
    }

    QString name() const
    {
        return m_name;
    }

    QString validatorName() const
    {
        return m_validatorName;
    }

    Qt::CaseSensitivity cs() const
    {
        return m_cs;
    }

private:
    QString m_name;
    QString m_validatorName;
    QRegularExpression m_regex;
    bool m_wildcard = false;
    bool m_optional = false;
    bool m_fixed = false;
    Qt::CaseSensitivity m_cs = Qt::CaseSensitive;
};


FLUGS_END_NAMESPACE

#endif

