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

#ifndef FLUGS_FOUNDATION_ABSTRACT_HTTP_PARSER_H
#define FLUGS_FOUNDATION_ABSTRACT_HTTP_PARSER_H

#include <Flugs/Foundation/Method>

FLUGS_BEGIN_NAMESPACE

/**
 * @brief The abstract http parser class
 */
class FLUGS_FOUNDATION_EXPORT AbstractHttpParser
{
public:
    /**
     * @brief Type of the message to parse
     */
    enum class Type
    {
        Request,  //!< Parse a http request
        Response, //!< Parse a http response
        Both      //!< Parse both
    };

    /**
     * @brief The Status enumeration indicates the result of a parse() method call.
     */
    enum class Status
    {
        Ok,                      //!<
        Upgrade,                 //!<
        OnMessageBeginFailed,    //!<
        OnUrlFailed,             //!<
        OnHeaderValueFailed,     //!<
        OnHeadersCompleteFailed, //!<
        OnBodyFailed,            //!<
        OnMessageCompleteFailed, //!<
        OnStatusFailed,          //!<
        OnChunkHeaderFailed,     //!<
        OnChunkCompleteFailed,   //!<
        InvalidEOF,              //!<
        HeaderOverflow,          //!<
        ClosedConnection,        //!<
        InvalidVersion,          //!<
        InvalidStatus,           //!<
        InvalidMethod,           //!<
        InvalidUrl,              //!<
        InvalidHost,             //!<
        InvalidPort,             //!<
        InvalidPath,             //!<
        InvalidQueryString,      //!<
        InvalidFragment,         //!<
        LineFeedExpected,        //!<
        InvalidHeaderToken,      //!<
        InvalidContentLength,    //!<
        UnexpectedContentLength, //!<
        InvalidChunkSize,        //!<
        InvalidConstant,         //!<
        InvalidInternalState,    //!<
        StrictAssertionFailed,   //!<
        Paused,                  //!<
        UnknownError             //!<
    };

    /**
     * @brief Contructs a new parser.
     */
    explicit AbstractHttpParser(Type type = Type::Request);

    /**
     * @brief Destroys the parser.
     */
    virtual ~AbstractHttpParser();

protected:
    /**
     * @brief Parse the message or the chunk of a message
     */
    Status parse(const char* data, quint64 size);

    /**
     * @brief The http method
     */
    Method method() const;

    /**
     * @ brief The content size of the body
     */
    quint64 contentLength() const;

    /**
     * @brief The http major version
     */
    quint8 httpMajor() const;

    /**
     * @brief The http minor version
     */
    quint8 httpMinor() const;

    /**
     * @brief Callback to notify that parsing of a new message begins.
     */
    virtual bool onMessageBegin() = 0;

    /**
     * @brief Callback to set the parsed url.
     */
    virtual bool onUrl(const QByteArray& data) = 0;

    /**
     * @brief Callback to add a header key/value pair.
     */
    virtual bool onHeaderValue(const QByteArray& name, const QByteArray& value) = 0;

    /**
     * @brief Callback to notify that the http header has been parsed.
     */
    virtual bool onHeadersComplete() = 0;

    /**
     * @brief Callback to add (a chunk of) the body data.
     */
    virtual bool onBody(const QByteArray& data) = 0;

    /**
     * @brief Callback to notify that the message has been parsed.
     */
    virtual bool onMessageComplete() = 0;

    /**
     * @brief Callback to set the http status.
     */
    virtual bool onStatus(const QByteArray& data);

    /**
     * @brief Callback to notify the begin of a single data chunk
     */
    virtual bool onChunkHeader();

    /**
     * @brief Callback to notify the end of a single data chunk
     */
    virtual bool onChunkComplete();

private:
    struct Private;
    friend struct Private;
    Private* d = nullptr;
};

FLUGS_END_NAMESPACE

#endif
