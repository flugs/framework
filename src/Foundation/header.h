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
#ifndef FLUGS_FOUNDATION_HEADER_H
#define FLUGS_FOUNDATION_HEADER_H

#include <Flugs/Foundation/Global>

FLUGS_BEGIN_NAMESPACE

class FLUGS_FOUNDATION_EXPORT Header
{
public:
    enum Name
    {
        // clang-format off
        Other, //!<
        // standard http request headers
        Accept,                   //!< Acceptable content-types
        AcceptCharset,            //!< Acceptable character sets
        AcceptEncoding,           //!< List of acceptable encodings
        AcceptLanguage,           //!< List of acceptable languages
        AcceptDatetime,           //!< Acceptable version in time
        Authorization,            //!< Authentication credentials for HTTP authentication
        Cookie,                   //!< The cookie previously sent by the server
        Expect,                   //!< The expected server behavoir
        From,                     //!< The email address of the user making the request
        Host,                     //!< Domain name of the server and the port number, if the port is not the standard port
        IfMatch,                  //!< Only perform the requested action if the entity is unchanged.
        IfModifiedSince,          //!< Allow a "304 Not Modified" if the entity is unchanged.
        IfNoneMatch,              //!< Allow a "304 Not Modified" if the entity is unchanged.
        IfRange,                  //!< Send the requested range if the entity is unchanged, otherwise send the entire entity
        IfUnmodifiedSince,        //!< Only send the response if the entity has not been modified since a specific time
        MaxForwards,              //!< Limit the number of times the message can be forwarded through proxies or gateways
        Origin,                   //!< Initiates a request for cross-origin resource sharing
        ProxyAuthorization,       //!< Authorization credentials for connecting to a proxy
        Range,                    //!< Request only a part of the entity.
        Referrer,                 //!< The previous web page from which a link to the current requested page was followed. @note The word "referrer" was misspelled in the RFC and so adopted by many implementations. Today the misspelled form has become standard usage.
        Te,                       //!< The transfer encodings the user agent will accept
        UserAgent,                //!< The user agent string
        // common non-standard http request headers
        Dnt,                      //!< Request to enable/disable tracking the user
        XRequestedWith,           //!< Used to identify Ajax requests
        XForwardedFor,            //!< The original IP address of the client when connecting trough an proxy server
        XForwardedHost,           //!< The original host name of the client when connecting trough an proxy server
        XForwardedProto,          //!< The original protocol of the client
        XHttpMethodOverride,      //!< Override the request method with the given method. Helpful if a fucking stupid sysadmin wants to kill the Internet and forbids PUT or DELETE methods
        XWapProfile,              //!< A link to an XML file (on the Internet) with a description of the device currently connecting.
        // standard http response headers
        AccessControlAllowOrigin, //!< Specifies which websites are allowed to participate in cross-origin resource sharing
        AcceptRanges,             //!< The content rages this server supports
        Age,                      //!< Seconds the entity was cached in a proxy
        Allow,                    //!< Valid actions for the resource. Used within a "405 Method not allowed" response
        ContentEncoding,          //!< The type of encoding used on the data
        ContentLanguage,          //!< The content language
        ContentLocation,          //!< Alternate location for the data
        ContentDisposition,       //!< Indicates that the content is a file and recommends to store it under the given file name
        ContentRange,             //!< The range of the message
        ETag,                     //!< Identifier for a specific version of a resource
        Expires,                  //!< Gives the date/time after which the response is considered stale
        LastModified,             //!< The last modified date for the requested object
        Link,                     //!< Used to express a relationship with another resource, where the relation type is defined by RFC 5988
        Location,                 //!< Used in redirection, or when a new resource has been created
        P3P,                      //!< This field is supposed to set P3P policy
        ProxyAuthenticate,        //!< Request authentication to access the proxy
        Refresh,                  //!< Used in redirection, or when a new resource has been created
        RetryAfter,               //!< If an entity is temporarily unavailable, this instructs the client to try again later
        Server,                   //!< A name for the server
        SetCookie,                //!< An HTTP cookie
        Status,                   //!< The status of the HTTP response
        StrictTransportSecurity,  //!< HSTS is a security policy mechanism which helps to protect against protocol downgrade attacks and cookie hijacking
        Trailer,                  //!< Indicates that the given set of header fields is present in the trailer
        TransferEncoding,         //!< Encoding used to safely transfer the entity to the user
        Vary,                     //!< Tells downstream proxies how to match future request headers to decide whether the cached response can be used rather than requesting a fresh one from the origin server
        WwwAuthenticate,          //!< Indicates the authentication scheme that should be used to access the requested entity
        // common non-standard http response headers
        PublicKeyPins,            //!< Announce and pin the hash of the TLS certificate
        ContentSecurityPolicy,    //!< CSP (content security policy) definition
        XXssProtection,           //!< XSS (cross site scripting) filter
        XPoweredBy,               //!< ...shameless self plug
        XUaCompatible,            //!< The recommended rendering engine
        // standard http request/response headers
        CacheControl,             //!< Control the caching mechanism
        Connection,               //!< Prefered connection type
        ContentLength,            //!< The length of the body
        ContentMd5,               //!< Base64 encoded MD5 sum of the body
        ContentType,              //!< The MIME type of the body
        Date,                     //!< Date and time the message was send
        Pragma,                   //!< Field with implementation specific values
        Upgrade,                  //!< Request the receiver to upgrade to another protocol
        Via,                      //!< The proxies through which the request/response was send
        Warning                   //!< General warning about possible problems with the body content
        // clang-format on
    };

    /**
     *
     */
    Header();

    /**
     *
     */
    explicit Header(Header::Name name, const QByteArray& value);

    /**
     *
     */
    explicit Header(Header::Name name, const QList<QByteArray>& values);

    /**
     *
     */
    explicit Header(const QByteArray& name, const QByteArray& value);

    /**
     *
     */
    explicit Header(const QByteArray& name, const QList<QByteArray>& values);

    /**
     *
     */
    bool isValid() const;

    /**
     *
     */
    QByteArray name() const;

    /**
     *
     */
    Header::Name headerName() const;

    /**
     *
     */
    QByteArray value() const;

    /**
     *
     */
    void appendValue(const QByteArray& value);

    /**
     *
     */
    void appendValue(const QList<QByteArray>& values);

    /**
     *
     */
    void removeOneValue(const QByteArray& value);

    /**
     *
     */
    void removeAllValue(const QByteArray& value);

    /**
     *
     */
    QList<QByteArray> values() const;

    /**
     *
     */
    static Header::Name toHeaderName(const QByteArray& value);

    /**
     *
     */
    static QByteArray fromHeaderName(Header::Name& value);

private:
    QByteArray m_name;
    QList<QByteArray> m_values;
};

inline uint qHash(const Header::Name headerName, uint seed = 0)
{
    return ::qHash(static_cast<int>(headerName), seed);
}

inline uint qHash(const Header& header, uint seed = 0)
{
    return ::qHash(header.name().toLower(), seed) ^ qHash(header.values(), seed);
}

FLUGS_END_NAMESPACE

inline bool operator==(const FLUGS_NAMESPACE_PREFIX Header& lhs, const FLUGS_NAMESPACE_PREFIX Header& rhs)
{
    return lhs.name().toLower() == rhs.name().toLower() && lhs.values() == rhs.values();
}

inline bool operator!=(const FLUGS_NAMESPACE_PREFIX Header& lhs, const FLUGS_NAMESPACE_PREFIX Header& rhs)
{
    return !(lhs == rhs);
}

#endif
