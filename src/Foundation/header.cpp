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
#include "header.h"

FLUGS_USE_NAMESPACE

// clang-format off
static const QHash<Header::Name, QByteArray> s_lookup( {
    { Header::Name::Other,                     QByteArrayLiteral("")                             },
    { Header::Name::Accept,                    QByteArrayLiteral("Accept")                       },
    { Header::Name::AcceptCharset,             QByteArrayLiteral("Accept-Charset")               },
    { Header::Name::AcceptEncoding,            QByteArrayLiteral("Accept-Encoding")              },
    { Header::Name::AcceptLanguage,            QByteArrayLiteral("Accept-Language")              },
    { Header::Name::AcceptDatetime,            QByteArrayLiteral("Accept-Datetime")              },
    { Header::Name::Authorization,             QByteArrayLiteral("Authorization")                },
    { Header::Name::Cookie,                    QByteArrayLiteral("Cookie")                       },
    { Header::Name::Expect,                    QByteArrayLiteral("Expect")                       },
    { Header::Name::From,                      QByteArrayLiteral("From")                         },
    { Header::Name::Host,                      QByteArrayLiteral("Host")                         },
    { Header::Name::IfMatch,                   QByteArrayLiteral("If-Match")                     },
    { Header::Name::IfModifiedSince,           QByteArrayLiteral("If-Modified-Since")            },
    { Header::Name::IfNoneMatch,               QByteArrayLiteral("If-None-Match")                },
    { Header::Name::IfRange,                   QByteArrayLiteral("If-Range")                     },
    { Header::Name::IfUnmodifiedSince,         QByteArrayLiteral("If-Unmodified-Since")          },
    { Header::Name::MaxForwards,               QByteArrayLiteral("Max-Forwards")                 },
    { Header::Name::Origin,                    QByteArrayLiteral("Origin")                       },
    { Header::Name::ProxyAuthorization,        QByteArrayLiteral("Proxy-Authorization")          },
    { Header::Name::Range,                     QByteArrayLiteral("Range")                        },
    { Header::Name::Referrer,                  QByteArrayLiteral("Referrer")                     },
    { Header::Name::Te,                        QByteArrayLiteral("TE")                           },
    { Header::Name::UserAgent,                 QByteArrayLiteral("User-Agent")                   },
    { Header::Name::Dnt,                       QByteArrayLiteral("DNT")                          },
    { Header::Name::XRequestedWith,            QByteArrayLiteral("X-Requested-With")             },
    { Header::Name::XForwardedFor,             QByteArrayLiteral("X-Forwarded-For")              },
    { Header::Name::XForwardedHost,            QByteArrayLiteral("X-Forwarded-Host")             },
    { Header::Name::XForwardedProto,           QByteArrayLiteral("X-Forwarded-Proto")            },
    { Header::Name::XHttpMethodOverride,       QByteArrayLiteral("X-HTTP-Method-Override")       },
    { Header::Name::XWapProfile,               QByteArrayLiteral("x-wap-profile")                },
    { Header::Name::AccessControlAllowOrigin,  QByteArrayLiteral("Access-Control-Allow-Origin")  },
    { Header::Name::AcceptRanges,              QByteArrayLiteral("Accept-Ranges")                },
    { Header::Name::Age,                       QByteArrayLiteral("Age")                          },
    { Header::Name::Allow,                     QByteArrayLiteral("Allow")                        },
    { Header::Name::ContentEncoding,           QByteArrayLiteral("Content-Encoding")             },
    { Header::Name::ContentLanguage,           QByteArrayLiteral("Content-Language")             },
    { Header::Name::ContentLocation,           QByteArrayLiteral("Content-Location")             },
    { Header::Name::ContentDisposition,        QByteArrayLiteral("Content-Disposition")          },
    { Header::Name::ContentRange,              QByteArrayLiteral("Content-Range")                },
    { Header::Name::ETag,                      QByteArrayLiteral("ETag")                         },
    { Header::Name::Expires,                   QByteArrayLiteral("Expires")                      },
    { Header::Name::LastModified,              QByteArrayLiteral("Last-Modified")                },
    { Header::Name::Link,                      QByteArrayLiteral("Link")                         },
    { Header::Name::Location,                  QByteArrayLiteral("Location")                     },
    { Header::Name::P3P,                       QByteArrayLiteral("P3P")                          },
    { Header::Name::ProxyAuthenticate,         QByteArrayLiteral("Proxy-Authenticate")           },
    { Header::Name::Refresh,                   QByteArrayLiteral("Refresh")                      },
    { Header::Name::RetryAfter,                QByteArrayLiteral("Retry-After")                  },
    { Header::Name::Server,                    QByteArrayLiteral("Server")                       },
    { Header::Name::SetCookie,                 QByteArrayLiteral("Set-Cookie")                   },
    { Header::Name::Status,                    QByteArrayLiteral("Status")                       },
    { Header::Name::StrictTransportSecurity,   QByteArrayLiteral("Strict-Transport-Security")    },
    { Header::Name::Trailer,                   QByteArrayLiteral("Trailer")                      },
    { Header::Name::TransferEncoding,          QByteArrayLiteral("Transfer-Encoding")            },
    { Header::Name::Vary,                      QByteArrayLiteral("Vary")                         },
    { Header::Name::WwwAuthenticate,           QByteArrayLiteral("WWW-Authenticate")             },
    { Header::Name::PublicKeyPins,             QByteArrayLiteral("Public-Key-Pins")              },
    { Header::Name::ContentSecurityPolicy,     QByteArrayLiteral("Content-Security-Policy")      },
    { Header::Name::XXssProtection,            QByteArrayLiteral("X-XSS-Protection")             },
    { Header::Name::XPoweredBy,                QByteArrayLiteral("X-Powered-By")                 },
    { Header::Name::XUaCompatible,             QByteArrayLiteral("X-UA-Compatible")              },
    { Header::Name::CacheControl,              QByteArrayLiteral("Cache-Control")                },
    { Header::Name::Connection,                QByteArrayLiteral("Connection")                   },
    { Header::Name::ContentLength,             QByteArrayLiteral("Content-Length")               },
    { Header::Name::ContentMd5,                QByteArrayLiteral("Content-MD5")                  },
    { Header::Name::ContentType,               QByteArrayLiteral("Content-Type")                 },
    { Header::Name::Date,                      QByteArrayLiteral("Date")                         },
    { Header::Name::Pragma,                    QByteArrayLiteral("Pragma")                       },
    { Header::Name::Upgrade,                   QByteArrayLiteral("Upgrade")                      },
    { Header::Name::Via,                       QByteArrayLiteral("Via")                          },
    { Header::Name::Warning,                   QByteArrayLiteral("Warning")                      }
} );
// clang-format on

Header::Header()
{
}

Header::Header(Header::Name key, const QByteArray& value)
    : m_name(fromHeaderName(key))
    , m_values({ value })
{
}

Header::Header(Header::Name key, const QList<QByteArray>& values)
    : m_name(fromHeaderName(key))
    , m_values(values)
{
}

Header::Header(const QByteArray& key, const QByteArray& value)
    : m_name(key)
    , m_values({ value })
{
}

Header::Header(const QByteArray& key, const QList<QByteArray>& values)
    : m_name(key)
    , m_values(values)
{
}

bool Header::isValid() const
{
    return !m_name.isEmpty();
}

QByteArray Header::name() const
{
    return m_name;
}

Header::Name Header::headerName() const
{
    return toHeaderName(m_name);
}

QByteArray Header::value() const
{
    return m_values.value(0);
}

void Header::appendValue(const QByteArray& value)
{
    m_values.append(value);
}

void Header::appendValue(const QList<QByteArray>& values)
{
    m_values.append(values);
}

void Header::removeOneValue(const QByteArray& value)
{
    m_values.removeOne(value);
}

void Header::removeAllValue(const QByteArray& value)
{
    m_values.removeAll(value);
}

QList<QByteArray> Header::values() const
{
    return m_values;
}

Header::Name Header::toHeaderName(const QByteArray& value)
{
    return s_lookup.key(value);
}

QByteArray Header::fromHeaderName(Header::Name& value)
{
    return s_lookup.value(value);
}
