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
#ifndef FLUGS_FOUNDATION_STATUS_H
#define FLUGS_FOUNDATION_STATUS_H

#include <Flugs/Foundation/Global>

FLUGS_BEGIN_NAMESPACE

/**
 * @brief Defines all standard HTTP status codes and also a few more.
 */
class FLUGS_FOUNDATION_EXPORT Status
{
    Q_GADGET

    Q_PROPERTY(Status::Code code READ code CONSTANT)
    Q_PROPERTY(Status::Family family READ family CONSTANT)
    Q_PROPERTY(int number READ number CONSTANT)
    Q_PROPERTY(QString reasonPhrase READ reasonPhrase CONSTANT)

public:
    /**
     * @brief An enumeration representing the class of status code.
     */
    enum class Family
    {
        // clang-format off
        Other         =   0,  //!<
        Informational = 100,  //!< Request received, continuing process
        Successful    = 200,  //!< Request was received, understood, accepted, and processed successfully
        Redirection   = 300,  //!< The client must take additional action to complete the request
        ClientError   = 400,  //!< The client seems to have erred
        ServerError   = 500   //!< The server failed to fulfill an apparently valid request
        // clang-format on
    };
    Q_ENUM(Family)

    /**
     * @brief Commonly used status codes defined by HTTP
     *
     * @link https://httpstatuses.com
     * @link http://www.restapitutorial.com/httpstatuscodes.html
     */
    enum Code
    {
        // clang-format off
        Other                              = 000, //!<
        // --- 1xx - Informational
        Continue                           = 100, //!< @link https://httpstatuses.com/100
        SwitchingProtocols                 = 101, //!< @link https://httpstatuses.com/101
        Processing                         = 102, //!< @link https://httpstatuses.com/102
        // --- 2xx - Success
        Ok                                 = 200, //!< @link https://httpstatuses.com/200
        Created                            = 201, //!< @link https://httpstatuses.com/201
        Accepted                           = 202, //!< @link https://httpstatuses.com/202
        NonAuthoritativeInformation        = 203, //!< @link https://httpstatuses.com/203
        NoContent                          = 204, //!< @link https://httpstatuses.com/204
        ResetContent                       = 205, //!< @link https://httpstatuses.com/205
        PartialContent                     = 206, //!< @link https://httpstatuses.com/206
        MultiStatus                        = 207, //!< @link https://httpstatuses.com/207
        AlreadyReported                    = 208, //!< @link https://httpstatuses.com/208
        ImUsed                             = 226, //!< @link https://httpstatuses.com/226
        // --- 3xx - Redirection
        MultipleChoice                     = 300, //!< @link https://httpstatuses.com/300
        MovedPermanently                   = 301, //!< @link https://httpstatuses.com/301
        Found                              = 302, //!< @link https://httpstatuses.com/302
        SeeOther                           = 303, //!< @link https://httpstatuses.com/303
        NotModified                        = 304, //!< @link https://httpstatuses.com/304
        UseProxy                           = 305, //!< @link https://httpstatuses.com/305
        TemporaryRedirect                  = 307, //!< @link https://httpstatuses.com/307
        PermanentRedirect                  = 308, //!< @link https://httpstatuses.com/308
        // --- 4xx - Client Error
        BadRequest                         = 400, //!< @link https://httpstatuses.com/400
        Unauthorized                       = 401, //!< @link https://httpstatuses.com/401
        PaymentRequired                    = 402, //!< @link https://httpstatuses.com/402
        Forbidden                          = 403, //!< @link https://httpstatuses.com/403
        NotFound                           = 404, //!< @link https://httpstatuses.com/404
        MethodNotAllowed                   = 405, //!< @link https://httpstatuses.com/405
        NotAcceptable                      = 406, //!< @link https://httpstatuses.com/406
        ProxyAuthenticationRequired        = 407, //!< @link https://httpstatuses.com/407
        RequestTimeout                     = 408, //!< @link https://httpstatuses.com/408
        Conflict                           = 409, //!< @link https://httpstatuses.com/409
        Gone                               = 410, //!< @link https://httpstatuses.com/410
        LengthRequired                     = 411, //!< @link https://httpstatuses.com/411
        PreconditionFailed                 = 412, //!< @link https://httpstatuses.com/412
        RequestEntityTooLarge              = 413, //!< @link https://httpstatuses.com/413
        RequestUriTooLong                  = 414, //!< @link https://httpstatuses.com/414
        UnsupportedMediaType               = 415, //!< @link https://httpstatuses.com/415
        RequestedRangeNotSatisfiable       = 416, //!< @link https://httpstatuses.com/416
        ExpectationFailed                  = 417, //!< @link https://httpstatuses.com/417
        ImATeapot                          = 418, //!< @link https://httpstatuses.com/418
        PolicyNotFulfilled                 = 420, //!< @link https://httpstatuses.com/420
        MisdirectedRequest                 = 421, //!< @link https://httpstatuses.com/421
        UnprocessableEntity                = 422, //!< @link https://httpstatuses.com/422
        Locked                             = 423, //!< @link https://httpstatuses.com/423
        FailedDependency                   = 424, //!< @link https://httpstatuses.com/424
        UnorderedCollection                = 425, //!< @link https://httpstatuses.com/425
        UpgradeRequired                    = 426, //!< @link https://httpstatuses.com/426
        PreconditionRequired               = 428, //!< @link https://httpstatuses.com/428
        TooManyRequests                    = 429, //!< @link https://httpstatuses.com/429
        RequestHeaderFieldsTooLarge        = 431, //!< @link https://httpstatuses.com/431
        LoginTimeout                       = 440, //!< @link https://httpstatuses.com/440
        ConnectionClosedWithoutResponse    = 444, //!< @link https://httpstatuses.com/444
        RetryWith                          = 449, //!< @link https://httpstatuses.com/449
        BlockedByWindowsParentalControl    = 450, //!< @link https://httpstatuses.com/450
        UnavailableForLegalReasons         = 451, //!< @link https://httpstatuses.com/451
        SslCertificateError                = 495, //!< @link https://httpstatuses.com/495
        SslCertificateRequired             = 496, //!< @link https://httpstatuses.com/496
        HttpRequestSendToHttpsPort         = 496, //!< @link https://httpstatuses.com/497
        ClientClosedRequest                = 499, //!< @link https://httpstatuses.com/499
        // --- 5xx - Server Error
        InternalServerError                = 500, //!< @link https://httpstatuses.com/500
        NotImplemented                     = 501, //!< @link https://httpstatuses.com/501
        BadGateway                         = 502, //!< @link https://httpstatuses.com/502
        ServiceUnavailable                 = 503, //!< @link https://httpstatuses.com/503
        GatewayTimeout                     = 504, //!< @link https://httpstatuses.com/504
        HttpVersionNotSupported            = 505, //!< @link https://httpstatuses.com/505
        VariantAlsoNegotiates              = 506, //!< @link https://httpstatuses.com/506
        InsufficientStorage                = 507, //!< @link https://httpstatuses.com/507
        LoopDetected                       = 508, //!< @link https://httpstatuses.com/508
        BandwidthLimitExceeded             = 509, //!< @link https://httpstatuses.com/509
        NotExtended                        = 510, //!< @link https://httpstatuses.com/510
        NetworkAuthenticationRequired      = 511, //!< @link https://httpstatuses.com/511
        NetworkReadTimeoutError            = 598, //!< @link https://httpstatuses.com/598
        NetworkConnectTimeoutError         = 599, //!< @link https://httpstatuses.com/599
        // clang-format on
    };
    Q_ENUM(Code)

    /**
     * @brief Constructs a OTHER status.
     */
    Q_INVOKABLE Status()
        : m_code(Status::Code::Other)
        , m_number(static_cast<int>(Status::Code::Other))
    {
    }

    /**
     * @brief Constructs a Status initialized with @p code
     */
    explicit Status(Status::Code code)
        : m_code(code)
        , m_number(static_cast<int>(code))
    {
    }

    /**
     * @brief Constructs a Status initialized with @p statusCode
     */
    explicit Status(int statusCode);

    /**
     * @brief Get the status code
     */
    Status::Code code() const
    {
        return m_code;
    }

    /**
     * @brief Get the associated status code number
     */
    int number() const
    {
        return m_number;
    }

    /**
     * @brief Get the class of status code
     */
    Family family() const;

    /**
     * @brief Get the reason phrase
     */
    QString reasonPhrase() const;

private:
    Code m_code;
    int m_number;
};

inline uint qHash(const Status::Code statusCode, uint seed = 0)
{
    return ::qHash(static_cast<int>(statusCode), seed);
}

inline uint qHash(const Status::Family statusFamily, uint seed = 0)
{
    return ::qHash(static_cast<int>(statusFamily), seed);
}

inline uint qHash(const Status& status, uint seed = 0)
{
    return ::qHash(status.number(), seed);
}

FLUGS_END_NAMESPACE

Q_DECLARE_TYPEINFO(FLUGS_NAMESPACE_PREFIX Status, Q_PRIMITIVE_TYPE);

inline bool operator==(const FLUGS_NAMESPACE_PREFIX Status& lhs, const FLUGS_NAMESPACE_PREFIX Status& rhs)
{
    return lhs.number() == rhs.number();
}

inline bool operator!=(const FLUGS_NAMESPACE_PREFIX Status& lhs, const FLUGS_NAMESPACE_PREFIX Status& rhs)
{
    return !(lhs == rhs);
}

inline bool operator==(const FLUGS_NAMESPACE_PREFIX Status& lhs, int rhs)
{
    return lhs.number() == rhs;
}

inline bool operator!=(const FLUGS_NAMESPACE_PREFIX Status& lhs, int rhs)
{
    return !(lhs == rhs);
}

inline bool operator==(int lhs, const FLUGS_NAMESPACE_PREFIX Status& rhs)
{
    return lhs == rhs.number();
}

inline bool operator!=(int lhs, const FLUGS_NAMESPACE_PREFIX Status& rhs)
{
    return !(lhs == rhs);
}

#endif
