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
#include "method.h"

#include <QHash>

FLUGS_USE_NAMESPACE

// clang-format off
static const QHash<QString, Method::Type> lookup( {
    { QStringLiteral(""),               Method::Type::Other       },

    { QStringLiteral("GET"),            Method::Type::Get         },
    { QStringLiteral("POST"),           Method::Type::Post        },
    { QStringLiteral("PUT"),            Method::Type::Put         },
    { QStringLiteral("PATCH"),          Method::Type::Patch       },
    { QStringLiteral("DELETE"),         Method::Type::Delete      },
    { QStringLiteral("TRACE"),          Method::Type::Trace       },
    { QStringLiteral("OPTIONS"),        Method::Type::Options     },
    { QStringLiteral("CONNECT"),        Method::Type::Connect     },
    { QStringLiteral("PURGE"),          Method::Type::Purge       },
    { QStringLiteral("LINK"),           Method::Type::Link        },
    { QStringLiteral("UNLINK"),         Method::Type::Unlink      },

    // -- WebDAV
    { QStringLiteral("PROPFIND"),       Method::Type::PropFind    },
    { QStringLiteral("PROPPATCH"),      Method::Type::PropPatch   },
    { QStringLiteral("MKCOL"),          Method::Type::MkCol       },
    { QStringLiteral("COPY"),           Method::Type::Copy        },
    { QStringLiteral("MOVE"),           Method::Type::Move        },
    { QStringLiteral("LOCK"),           Method::Type::Lock        },
    { QStringLiteral("UNLOCK"),         Method::Type::Unlock      },
    { QStringLiteral("SEARCH"),         Method::Type::Search      },
    { QStringLiteral("BIND"),           Method::Type::Bind        },
    { QStringLiteral("REBIND"),         Method::Type::Rebind      },
    { QStringLiteral("UNBIND"),         Method::Type::Unbind      },
    { QStringLiteral("ACL"),            Method::Type::Acl         },

    // --- CalDAV
    { QStringLiteral("MKCALENDAR"),     Method::Type::MkCalendar  },

    // --- Subversion
    { QStringLiteral("REPORT"),         Method::Type::Report      },
    { QStringLiteral("MKACTIVITY"),     Method::Type::MkActivity  },
    { QStringLiteral("CHECKOUT"),       Method::Type::Checkout    },
    { QStringLiteral("MERGE"),          Method::Type::Merge       },

    // --- UPnP
    { QStringLiteral("MSEARCH"),        Method::Type::MSearch     },
    { QStringLiteral("NOTIFY"),         Method::Type::Notify      },
    { QStringLiteral("SUBSCRIBE"),      Method::Type::Subscribe   },
    { QStringLiteral("UNSUBSCRIBE"),    Method::Type::Unsubscribe }
});
// clang-format on

Method::Method()
{
}

Method::Method(Method::Type type)
{
    m_type = type;
    m_name = lookup.key(m_type);
}

Method::Method(const QString& name)
{
    const QString value = name.trimmed().toUpper();
    m_type = lookup.value(value, Type::Other);
    m_name = value;
}
