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
#ifndef FLUGS_FOUNDATION_METHOD_H
#define FLUGS_FOUNDATION_METHOD_H

#include <Flugs/Foundation/Global>

FLUGS_BEGIN_NAMESPACE

class AbstractHttpParser;

class FLUGS_FOUNDATION_EXPORT Method
{
    Q_GADGET
    Q_PROPERTY(Type type READ type CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)

public:
    enum Type
    {
        // clang-format off
        Other          = -1,

        Get            =  1,        //!< GET
        Post           =  2,        //!< POST
        Head           =  3,        //!< HEAD
        Put            =  4,        //!< PUT
        Patch          =  5,        //!< PATCH
        Delete         =  6,        //!< DELETE
        Trace          =  7,        //!< TRACE
        Options        =  8,        //!< OPTIONS
        Connect        =  9,        //!< CONNECT
        Purge          = 10,        //!< PURGE
        Link           = 11,        //!< LINK
        Unlink         = 12,        //!< UNLINK

        // --- WebDAV
        PropFind       = 101,       //!< PROPFIND
        PropPatch      = 102,       //!< PROPPATCH
        MkCol          = 103,       //!< MKCOL
        Copy           = 104,       //!< COPY
        Move           = 105,       //!< MOVE
        Lock           = 106,       //!< LOCK
        Unlock         = 107,       //!< UNLOCK
        Search         = 108,       //!< SEARCH
        Bind           = 109,       //!< BIND
        Rebind         = 110,       //!< REBIND
        Unbind         = 111,       //!< UNBIND
        Acl            = 112,       //!< ACL

        // --- CalDAV
        MkCalendar     = 151,       //!< MKCALENDAR

        /* Subversion */
        Report         = 201,       //!< REPORT
        MkActivity     = 202,       //!< MKACTIVITY
        Checkout       = 203,       //!< CHECKOUT
        Merge          = 204,       //!< MERGE

        /* UPnP */
        MSearch        = 251,       //!< M-SEARCH
        Notify         = 252,       //!< NOTIFY
        Subscribe      = 253,       //!< SUBSCRIBE
        Unsubscribe    = 254        //!< UNSUBSCRIBE
        // clang-format on
    };
    Q_ENUM(Type)

    /**
     *
     */
    Q_INVOKABLE Method();

    /**
     *
     */
    Q_INVOKABLE explicit Method(Method::Type type);

    /**
     *
     */
    Q_INVOKABLE explicit Method(const QString& name);

    /**
     *
     */
    Method::Type type() const
    {
        return m_type;
    }

    /**
     *
     */
    QString name() const
    {
        return m_name;
    }

private:
    Method::Type m_type = Method::Type::Other;
    QString m_name;
};

FLUGS_END_NAMESPACE

Q_DECLARE_TYPEINFO(FLUGS_NAMESPACE_PREFIX Method, Q_PRIMITIVE_TYPE);

inline bool operator==(const FLUGS_NAMESPACE_PREFIX Method& lhs, const FLUGS_NAMESPACE_PREFIX Method& rhs)
{
    return (lhs.type() != FLUGS_NAMESPACE_PREFIX Method::Type::Other && lhs.type() == rhs.type()) || lhs.name() == rhs.name();
}

inline bool operator!=(const FLUGS_NAMESPACE_PREFIX Method& lhs, const FLUGS_NAMESPACE_PREFIX Method& rhs)
{
    return !(lhs == rhs);
}

inline bool operator==(const FLUGS_NAMESPACE_PREFIX Method& lhs, FLUGS_NAMESPACE_PREFIX Method::Type rhs)
{
    return lhs.type() == rhs;
}

inline bool operator!=(const FLUGS_NAMESPACE_PREFIX Method& lhs, FLUGS_NAMESPACE_PREFIX Method::Type rhs)
{
    return !(lhs == rhs);
}

inline bool operator==(FLUGS_NAMESPACE_PREFIX Method::Type lhs, const FLUGS_NAMESPACE_PREFIX Method& rhs)
{
    return lhs == rhs.type();
}

inline bool operator!=(FLUGS_NAMESPACE_PREFIX Method::Type lhs, const FLUGS_NAMESPACE_PREFIX Method& rhs)
{
    return !(lhs == rhs);
}

#endif
