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
#include "abstracthttpparser.h"

#include "http_parser.h"

FLUGS_USE_NAMESPACE

#define P static_cast<AbstractHttpParser::Private*>(p->data)
#define Q static_cast<AbstractHttpParser::Private*>(p->data)->q

struct AbstractHttpParser::Private
{
    Private(AbstractHttpParser::Type type, AbstractHttpParser* parent)
        : q(parent)
    {
        memset(&parser_settings, 0, sizeof(http_parser_settings));

        switch (type) {
        case AbstractHttpParser::Type::Request:
            http_parser_init(&parser, HTTP_REQUEST);
            break;
        case AbstractHttpParser::Type::Response:
            http_parser_init(&parser, HTTP_RESPONSE);
            break;
        case AbstractHttpParser::Type::Both:
            http_parser_init(&parser, HTTP_BOTH);
            break;
        }

        parser.data = this;
        parser_settings.on_message_begin = on_message_begin;
        parser_settings.on_url = on_url;
        parser_settings.on_status = on_status;
        parser_settings.on_header_field = on_header_field;
        parser_settings.on_header_value = on_header_value;
        parser_settings.on_headers_complete = on_headers_complete;
        parser_settings.on_body = on_body;
        parser_settings.on_message_complete = on_message_complete;
        parser_settings.on_chunk_header = on_chunk_header;
        parser_settings.on_chunk_complete = on_chunk_complete;
    }

    static int on_message_begin(http_parser* p)
    {
        return Q->onMessageBegin() ? 0 : 1;
    }

    static int on_url(http_parser* p, const char* at, size_t length)
    {
        return Q->onUrl(QByteArray(at, static_cast<int>(length))) ? 0 : 1;
    }

    static int on_status(http_parser* p, const char* at, size_t length)
    {
        return Q->onStatus(QByteArray(at, static_cast<int>(length))) ? 0 : 1;
    }

    static int on_header_field(http_parser* p, const char* at, size_t length)
    {
        // insert the header we parsed previously into the header map
        int status = P->notifyHeaderValue();
        P->currentHeaderField.append(at, static_cast<int>(length));

        return status;
    }

    static int on_header_value(http_parser* p, const char* at, size_t length)
    {
        P->currentHeaderValue.append(at, static_cast<int>(length));
        return 0;
    }

    static int on_headers_complete(http_parser* p)
    {
        P->notifyHeaderValue();
        return Q->onHeadersComplete() ? 0 : 1;
    }

    static int on_body(http_parser* p, const char* at, size_t length)
    {
        return Q->onBody(QByteArray(at, static_cast<int>(length))) ? 0 : 1;
    }

    static int on_message_complete(http_parser* p)
    {
        return Q->onMessageComplete() ? 0 : 1;
    }

    static int on_chunk_header(http_parser* p)
    {
        return Q->onChunkHeader() ? 0 : 1;
    }

    static int on_chunk_complete(http_parser* p)
    {
        return Q->onChunkComplete() ? 0 : 1;
    }

    int notifyHeaderValue()
    {
        int status = 0;
        if (!currentHeaderField.isEmpty() && !currentHeaderValue.isEmpty()) {
            qCDebug(LogParser) << "parsing header field/value:" << currentHeaderField << "=" << currentHeaderValue;
            status = q->onHeaderValue(currentHeaderField, currentHeaderValue) ? 0 : 1;

            // clear header value.
            currentHeaderField.clear();
            currentHeaderValue.clear();
        }

        return status;
    }

    http_parser parser;
    http_parser_settings parser_settings;
    AbstractHttpParser::Type type;
    QByteArray currentHeaderValue;
    QByteArray currentHeaderField;
    AbstractHttpParser* q = nullptr;
};

AbstractHttpParser::AbstractHttpParser(Type type)
    : d(new AbstractHttpParser::Private(type, this))
{
}

AbstractHttpParser::~AbstractHttpParser()
{
    delete d;
}

AbstractHttpParser::Status AbstractHttpParser::parse(const char* data, quint64 size)
{
    size_t len = static_cast<size_t>(size);
    size_t npos = http_parser_execute(&d->parser, &d->parser_settings, data, len);

    if (d->parser.upgrade) {
        return Status::Upgrade;
    }
    else if (npos != len) {
        switch (d->parser.http_errno) {
        case http_errno::HPE_OK:
            return Status::Ok;

        case http_errno::HPE_CB_message_begin:
            return Status::OnMessageBeginFailed;

        case http_errno::HPE_CB_url:
            return Status::OnUrlFailed;

        case http_errno::HPE_CB_header_field:
        case http_errno::HPE_CB_header_value:
            return Status::OnHeaderValueFailed;

        case http_errno::HPE_CB_headers_complete:
            return Status::OnHeadersCompleteFailed;

        case http_errno::HPE_CB_body:
            return Status::OnBodyFailed;

        case http_errno::HPE_CB_message_complete:
            return Status::OnMessageCompleteFailed;

        case http_errno::HPE_CB_status:
            return Status::OnStatusFailed;

        case http_errno::HPE_CB_chunk_header:
            return Status::OnChunkHeaderFailed;

        case http_errno::HPE_CB_chunk_complete:
            return Status::OnChunkCompleteFailed;

        case http_errno::HPE_INVALID_EOF_STATE:
            return Status::InvalidEOF;

        case http_errno::HPE_HEADER_OVERFLOW:
            return Status::HeaderOverflow;

        case http_errno::HPE_CLOSED_CONNECTION:
            return Status::ClosedConnection;

        case http_errno::HPE_INVALID_VERSION:
            return Status::InvalidVersion;

        case http_errno::HPE_INVALID_STATUS:
            return Status::InvalidStatus;

        case http_errno::HPE_INVALID_METHOD:
            return Status::InvalidMethod;

        case http_errno::HPE_INVALID_URL:
            return Status::InvalidUrl;

        case http_errno::HPE_INVALID_HOST:
            return Status::InvalidHost;

        case http_errno::HPE_INVALID_PORT:
            return Status::InvalidPort;

        case http_errno::HPE_INVALID_PATH:
            return Status::InvalidPath;

        case http_errno::HPE_INVALID_QUERY_STRING:
            return Status::InvalidQueryString;

        case http_errno::HPE_INVALID_FRAGMENT:
            return Status::InvalidFragment;

        case http_errno::HPE_LF_EXPECTED:
            return Status::LineFeedExpected;

        case http_errno::HPE_INVALID_HEADER_TOKEN:
            return Status::InvalidHeaderToken;

        case http_errno::HPE_INVALID_CONTENT_LENGTH:
            return Status::InvalidContentLength;

        case http_errno::HPE_UNEXPECTED_CONTENT_LENGTH:
            return Status::UnexpectedContentLength;

        case http_errno::HPE_INVALID_CHUNK_SIZE:
            return Status::InvalidChunkSize;

        case http_errno::HPE_INVALID_CONSTANT:
            return Status::InvalidConstant;

        case http_errno::HPE_INVALID_INTERNAL_STATE:
            return Status::InvalidInternalState;

        case http_errno::HPE_STRICT:
            return Status::StrictAssertionFailed;

        case http_errno::HPE_PAUSED:
            return Status::Paused;

        default:
            return Status::UnknownError;
        }
    }

    return Status::Ok;
}

bool AbstractHttpParser::onStatus(const QByteArray& data)
{
    Q_UNUSED(data);

    return true;
}

bool AbstractHttpParser::onChunkHeader()
{
    return true;
}

bool AbstractHttpParser::onChunkComplete()
{
    return true;
}

Method AbstractHttpParser::method() const
{
// clang-format off
#   define MK_CASE(x, y)  \
    case x:               \
        return Method(y);                                                                                                  \
    // clang-format on

    switch (static_cast<http_method>(d->parser.method)) {
        // clang-format off
      MK_CASE(http_method::HTTP_DELETE,      Method::Type::Delete      );
      MK_CASE(http_method::HTTP_GET,         Method::Type::Get         );
      MK_CASE(http_method::HTTP_HEAD,        Method::Type::Head        );
      MK_CASE(http_method::HTTP_POST,        Method::Type::Post        );
      MK_CASE(http_method::HTTP_PUT,         Method::Type::Put         );
      MK_CASE(http_method::HTTP_CONNECT,     Method::Type::Connect     );
      MK_CASE(http_method::HTTP_OPTIONS,     Method::Type::Options     );
      MK_CASE(http_method::HTTP_TRACE,       Method::Type::Trace       );
      MK_CASE(http_method::HTTP_COPY,        Method::Type::Copy        );
      MK_CASE(http_method::HTTP_LOCK,        Method::Type::Lock        );
      MK_CASE(http_method::HTTP_MKCOL,       Method::Type::MkCol       );
      MK_CASE(http_method::HTTP_MOVE,        Method::Type::Move        );
      MK_CASE(http_method::HTTP_PROPFIND,    Method::Type::PropFind    );
      MK_CASE(http_method::HTTP_PROPPATCH,   Method::Type::PropPatch   );
      MK_CASE(http_method::HTTP_SEARCH,      Method::Type::Search      );
      MK_CASE(http_method::HTTP_UNLOCK,      Method::Type::Unlock      );
      MK_CASE(http_method::HTTP_BIND,        Method::Type::Bind        );
      MK_CASE(http_method::HTTP_REBIND,      Method::Type::Rebind      );
      MK_CASE(http_method::HTTP_UNBIND,      Method::Type::Unbind      );
      MK_CASE(http_method::HTTP_ACL,         Method::Type::Acl         );
      MK_CASE(http_method::HTTP_REPORT,      Method::Type::Report      );
      MK_CASE(http_method::HTTP_MKACTIVITY,  Method::Type::MkActivity  );
      MK_CASE(http_method::HTTP_CHECKOUT,    Method::Type::Checkout    );
      MK_CASE(http_method::HTTP_MERGE,       Method::Type::Merge       );
      MK_CASE(http_method::HTTP_MSEARCH,     Method::Type::MSearch     );
      MK_CASE(http_method::HTTP_NOTIFY,      Method::Type::Notify      );
      MK_CASE(http_method::HTTP_SUBSCRIBE,   Method::Type::Subscribe   );
      MK_CASE(http_method::HTTP_UNSUBSCRIBE, Method::Type::Unsubscribe );
      MK_CASE(http_method::HTTP_PATCH,       Method::Type::Patch       );
      MK_CASE(http_method::HTTP_PURGE,       Method::Type::Purge       );
      MK_CASE(http_method::HTTP_MKCALENDAR,  Method::Type::MkCalendar  );
      MK_CASE(http_method::HTTP_LINK,        Method::Type::Link        );
      MK_CASE(http_method::HTTP_UNLINK,      Method::Type::Unlink      );
        // clang-format on
    }
#undef MK_CASE

    return Method();
}

quint64 AbstractHttpParser::contentLength() const
{
    return d->parser.content_length;
}

quint8 AbstractHttpParser::httpMajor() const
{
    return static_cast<quint8>(d->parser.http_major);
}

quint8 AbstractHttpParser::httpMinor() const
{
    return static_cast<quint8>(d->parser.http_minor);
}
