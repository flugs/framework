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
#include "status.h"

#include <QHash>

FLUGS_USE_NAMESPACE

// clang-format off
static const QHash<int, QString> s_lookup( {
  { static_cast<int>(Status::Code::Other),                           QStringLiteral("")                                    },

  // --- 1xx
  { static_cast<int>(Status::Code::Continue),                        QStringLiteral("Continue")                            },
  { static_cast<int>(Status::Code::SwitchingProtocols),              QStringLiteral("Switching Protocols")                 },
  { static_cast<int>(Status::Code::Processing),                      QStringLiteral("Processing")                          },

  // --- 2xx
  { static_cast<int>(Status::Code::Ok),                              QStringLiteral("OK")                                  },
  { static_cast<int>(Status::Code::Created),                         QStringLiteral("Created")                             },
  { static_cast<int>(Status::Code::Accepted),                        QStringLiteral("Accepted")                            },
  { static_cast<int>(Status::Code::NonAuthoritativeInformation),     QStringLiteral("Non-Authoritative Information")       },
  { static_cast<int>(Status::Code::NoContent),                       QStringLiteral("No Content")                          },
  { static_cast<int>(Status::Code::ResetContent),                    QStringLiteral("Reset Content")                       },
  { static_cast<int>(Status::Code::PartialContent),                  QStringLiteral("Partial Content")                     },
  { static_cast<int>(Status::Code::MultiStatus),                     QStringLiteral("Multi-Status")                        },
  { static_cast<int>(Status::Code::AlreadyReported),                 QStringLiteral("Already Reported")                    },
  { static_cast<int>(Status::Code::ImUsed),                          QStringLiteral("IM Used")                             },

  // -- 3xx
  { static_cast<int>(Status::Code::MultipleChoice),                  QStringLiteral("Multiple Choices")                    },
  { static_cast<int>(Status::Code::MovedPermanently),                QStringLiteral("Moved Permanently")                   },
  { static_cast<int>(Status::Code::Found),                           QStringLiteral("Found")                               },
  { static_cast<int>(Status::Code::SeeOther),                        QStringLiteral("See Other")                           },
  { static_cast<int>(Status::Code::NotModified),                     QStringLiteral("Not Modified")                        },
  { static_cast<int>(Status::Code::UseProxy),                        QStringLiteral("Use Proxy")                           },
  { static_cast<int>(Status::Code::TemporaryRedirect),               QStringLiteral("Temporary Redirect")                  },
  { static_cast<int>(Status::Code::PermanentRedirect),               QStringLiteral("Permanent Redirect")                  },

  // --- 4xx
  { static_cast<int>(Status::Code::BadRequest),                      QStringLiteral("Bad Request")                         },
  { static_cast<int>(Status::Code::Unauthorized),                    QStringLiteral("Unauthorized")                        },
  { static_cast<int>(Status::Code::PaymentRequired),                 QStringLiteral("Payment Required")                    },
  { static_cast<int>(Status::Code::Forbidden),                       QStringLiteral("Forbidden")                           },
  { static_cast<int>(Status::Code::NotFound),                        QStringLiteral("Not Found")                           },
  { static_cast<int>(Status::Code::MethodNotAllowed),                QStringLiteral("Method Not Allowed")                  },
  { static_cast<int>(Status::Code::NotAcceptable),                   QStringLiteral("Not Acceptable")                      },
  { static_cast<int>(Status::Code::ProxyAuthenticationRequired),     QStringLiteral("Proxy Authentication Required")       },
  { static_cast<int>(Status::Code::RequestTimeout),                  QStringLiteral("Request Timeout")                     },
  { static_cast<int>(Status::Code::Conflict),                        QStringLiteral("Conflict")                            },
  { static_cast<int>(Status::Code::Gone),                            QStringLiteral("Gone")                                },
  { static_cast<int>(Status::Code::LengthRequired),                  QStringLiteral("Length Required")                     },
  { static_cast<int>(Status::Code::PreconditionFailed),              QStringLiteral("Precondition Failed")                 },
  { static_cast<int>(Status::Code::RequestEntityTooLarge),           QStringLiteral("Request Entity Too Large")            },
  { static_cast<int>(Status::Code::RequestUriTooLong),               QStringLiteral("Request-URI Too Long")                },
  { static_cast<int>(Status::Code::UnsupportedMediaType),            QStringLiteral("Unsupported Media Type")              },
  { static_cast<int>(Status::Code::RequestedRangeNotSatisfiable),    QStringLiteral("Requested Range Not Satisfiable")     },
  { static_cast<int>(Status::Code::ExpectationFailed),               QStringLiteral("Expectation Failed")                  },
  { static_cast<int>(Status::Code::ImATeapot),                       QStringLiteral("I'm a teapot")                        },
  { static_cast<int>(Status::Code::PolicyNotFulfilled),              QStringLiteral("Policy Not Fulfilled")                },
  { static_cast<int>(Status::Code::MisdirectedRequest),              QStringLiteral("Misdirected Request")                 },
  { static_cast<int>(Status::Code::UnprocessableEntity),             QStringLiteral("Unprocessable Entity")                },
  { static_cast<int>(Status::Code::Locked),                          QStringLiteral("Locked")                              },
  { static_cast<int>(Status::Code::FailedDependency),                QStringLiteral("Failed Dependency")                   },
  { static_cast<int>(Status::Code::UnorderedCollection),             QStringLiteral("Unordered Collection")                },
  { static_cast<int>(Status::Code::UpgradeRequired),                 QStringLiteral("Upgrade Required")                    },
  { static_cast<int>(Status::Code::PreconditionRequired),            QStringLiteral("Precondition Required")               },
  { static_cast<int>(Status::Code::TooManyRequests),                 QStringLiteral("Too Many Requests")                   },
  { static_cast<int>(Status::Code::RequestHeaderFieldsTooLarge),     QStringLiteral("Request Header Fields Too Large")     },
  { static_cast<int>(Status::Code::LoginTimeout),                    QStringLiteral("Login Timeout")                       },
  { static_cast<int>(Status::Code::ConnectionClosedWithoutResponse), QStringLiteral("Connection Closed Without Response")  },
  { static_cast<int>(Status::Code::RetryWith),                       QStringLiteral("Retry With")                          },
  { static_cast<int>(Status::Code::BlockedByWindowsParentalControl), QStringLiteral("Blocked By Windows Parental Control") },
  { static_cast<int>(Status::Code::UnavailableForLegalReasons),      QStringLiteral("Unavailable For Legal Reasons")       },
  { static_cast<int>(Status::Code::SslCertificateError),             QStringLiteral("SSL Certificate Error")               },
  { static_cast<int>(Status::Code::SslCertificateRequired),          QStringLiteral("SSL Certificate Required")            },
  { static_cast<int>(Status::Code::HttpRequestSendToHttpsPort),      QStringLiteral("HTTP Request Sent to HTTPS Port")     },
  { static_cast<int>(Status::Code::ClientClosedRequest),             QStringLiteral("Client Closed Request")               },

  // --- 5xx
  { static_cast<int>(Status::Code::InternalServerError),             QStringLiteral("Internal Server Error")               },
  { static_cast<int>(Status::Code::NotImplemented),                  QStringLiteral("Not Implemented")                     },
  { static_cast<int>(Status::Code::BadGateway),                      QStringLiteral("Bad Gateway")                         },
  { static_cast<int>(Status::Code::ServiceUnavailable),              QStringLiteral("Service Unavailable")                 },
  { static_cast<int>(Status::Code::GatewayTimeout),                  QStringLiteral("Gateway Timeout")                     },
  { static_cast<int>(Status::Code::HttpVersionNotSupported),         QStringLiteral("HTTP Version Not Supported")          },
  { static_cast<int>(Status::Code::VariantAlsoNegotiates),           QStringLiteral("Variant Also Negotiates")             },
  { static_cast<int>(Status::Code::InsufficientStorage),             QStringLiteral("Insufficient Storage")                },
  { static_cast<int>(Status::Code::LoopDetected),                    QStringLiteral("Loop Detected")                       },
  { static_cast<int>(Status::Code::NotExtended),                     QStringLiteral("Not Extended")                        },
  { static_cast<int>(Status::Code::NetworkAuthenticationRequired),   QStringLiteral("Network Authentication Required")     },
  { static_cast<int>(Status::Code::NetworkReadTimeoutError),         QStringLiteral("Network Read Timeout Error")          },
  { static_cast<int>(Status::Code::NetworkConnectTimeoutError),      QStringLiteral("Network Connect Timeout Error")       }
});
// clang-format on

Status::Status(int statusCode)
    : m_code(Status::Code::Other)
    , m_number(statusCode)
{
    if (s_lookup.contains(m_number)) {
        m_code = static_cast<Status::Code>(m_number);
    }
}

Status::Family Status::family() const
{
    if (m_number >= 100 && m_number < 200) {
        return Family::Informational;
    }
    else if (m_number >= 200 && m_number < 300) {
        return Family::Successful;
    }
    else if (m_number >= 300 && m_number < 400) {
        return Family::Redirection;
    }
    else if (m_number >= 400 && m_number < 500) {
        return Family::ClientError;
    }
    else if (m_number >= 500 && m_number < 600) {
        return Family::ServerError;
    }

    return Family::Other;
}

QString Status::reasonPhrase() const
{
    return s_lookup.value(m_number);
}
