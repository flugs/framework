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
#include "headers.h"

FLUGS_USE_NAMESPACE

Headers::~Headers()
{
}

bool Headers::contains(const QByteArray& name) const
{
    return header(name).isValid();
}

bool Headers::contains(Header::Name name) const
{
    return header(name).isValid();
}

bool Headers::contains(Header::Name name, const QByteArray& value) const
{
    auto it = std::find_if(m_headers.cbegin(), m_headers.cend(), [name, value](const Header& h) { return h.headerName() == name && h.values().contains(value); });

    return it != m_headers.cend();
}

bool Headers::contains(Header::Name name, int value) const
{
    return contains(name, QString::number(value).toLatin1());
}

bool Headers::contains(Header::Name name, size_t value) const
{
    return contains(name, QString::number(value).toLatin1());
}

bool Headers::contains(Header::Name name, const QUrl& value) const
{
    return contains(name, value.toEncoded());
}

bool Headers::contains(const QByteArray& name, const QByteArray& value) const
{
    auto it = std::find_if(m_headers.cbegin(), m_headers.cend(), [name, value](const Header& h) { return qstricmp(h.name().constData(), name.constData()) == 0 && h.values().contains(value); });

    return it != m_headers.cend();
}

bool Headers::contains(const QByteArray& name, int value) const
{
    return contains(name, QString::number(value).toLatin1());
}

bool Headers::contains(const QByteArray& name, size_t value) const
{
    return contains(name, QString::number(value).toLatin1());
}

bool Headers::contains(const QByteArray& name, const QUrl& value) const
{
    return contains(name, value.toEncoded());
}

Header Headers::header(const QByteArray& name) const
{
    return header(name, Header());
}

Header Headers::header(Header::Name name) const
{
    return header(name, Header());
}

Header Headers::header(const QByteArray& name, const Header& defaultValue) const
{
    auto it = std::find_if(m_headers.cbegin(), m_headers.cend(), [name](const Header& h) { return h.name().toLower() == name.toLower(); });

    return it == m_headers.cend() ? defaultValue : *it;
}

Header Headers::header(Header::Name name, const Header& defaultValue) const
{
    return header(Header::fromHeaderName(name), defaultValue);
}

void Headers::insert(const Header& h)
{
    if (!h.isValid()) {
        return;
    }

    auto it = std::find_if(m_headers.begin(), m_headers.end(), [h](const Header& he) { return he.name().toLower() == h.name().toLower(); });

    if (it != m_headers.end()) {
        it->appendValue(h.values());
    }
    else {
        m_headers.append(h);
    }
}

void Headers::insert(Header::Name name, const QByteArray& value)
{
    insert(Header(name, value));
}

void Headers::insert(Header::Name name, int value)
{
    insert(Header(name, QString::number(value).toLatin1()));
}

void Headers::insert(Header::Name name, size_t value)
{
    insert(Header(name, QString::number(value).toLatin1()));
}

void Headers::insert(Header::Name name, const QUrl& value)
{
    insert(Header(name, value.toEncoded()));
}

void Headers::insert(Header::Name name, const QList<QByteArray>& values)
{
    insert(Header(name, values));
}

void Headers::insert(const QByteArray& name, const QByteArray& value)
{
    insert(Header(name, value));
}

void Headers::insert(const QByteArray& name, int value)
{
    insert(Header(name, QString::number(value).toLatin1()));
}

void Headers::insert(const QByteArray& name, size_t value)
{
    insert(Header(name, QString::number(value).toLatin1()));
}

void Headers::insert(const QByteArray& name, const QUrl& value)
{
    insert(Header(name, value.toEncoded()));
}

void Headers::insert(const QByteArray& name, const QList<QByteArray>& values)
{
    insert(Header(name, values));
}

int Headers::remove(Header::Name name)
{
    return 0;
}

int Headers::remove(Header::Name name, const QByteArray& value)
{
    return 0;
}

int Headers::remove(const Header& header)
{
    return 0;
}

int Headers::remove(const QByteArray& name)
{
    return 0;
}

int Headers::remove(const QByteArray& name, const QByteArray& value)
{
    return 0;
}
