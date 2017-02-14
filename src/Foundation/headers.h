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
#ifndef FLUGS_FOUNDATION_HEADERS_H
#define FLUGS_FOUNDATION_HEADERS_H

#include <QtCore/QMultiHash>

#include <Flugs/Foundation/Header>

FLUGS_BEGIN_NAMESPACE

/**
 * A map of request or response headers.
 */
class FLUGS_FOUNDATION_EXPORT Headers
{
public:
    virtual ~Headers();

    /**
     * @brief Returns true if the headers are empty; otherwise returns false
     */
    int isEmpty() const
    {
        return m_headers.isEmpty();
    }

    /**
     * @brief Returns the number of headers
     */
    int size() const
    {
        return m_headers.size();
    }

    /**
     * @brief Returns all headers
     */
    QList<Header> headers() const
    {
        return m_headers;
    }

    /**
     * @brief Returns true if the @p key exists; otherwise returns false
     */
    bool contains(Header::Name name) const;
    bool contains(const QByteArray& name) const;

    /**
     * @brief Returns true if a header @p name with value @p value exists; otherwise returns false
     */
    bool contains(Header::Name name, const QByteArray& value) const;
    bool contains(Header::Name name, int value) const;
    bool contains(Header::Name name, size_t value) const;
    bool contains(Header::Name name, const QUrl& value) const;
    bool contains(const QByteArray& name, const QByteArray& value) const;
    bool contains(const QByteArray& name, int value) const;
    bool contains(const QByteArray& name, size_t value) const;
    bool contains(const QByteArray& name, const QUrl& value) const;

    /**
     * @brief Returns the Header with the name @p name.
     */
    Header header(const QByteArray& name) const;

    /**
     * @brief Returns the Header with the name @p name.
     */
    Header header(Header::Name name) const;

    /**
     * @brief Returns the Header with the name @p name or @p defaultValue if no such header exists.
     */
    Header header(const QByteArray& name, const Header& defaultValue) const;

    /**
     * @brief Returns the Header with the name @p name or @p defaultValue if no such header exists.
     */
    Header header(Header::Name name, const Header& defaultValue) const;

    /**
     * @brief Inserts a new header with the @p key and a value of @p val.
     *
     * If there is already an header with the same @p key, this function
     * will simply create a new one.
     */
    void insert(const Header& header);
    void insert(Header::Name name, const QByteArray& value);
    void insert(Header::Name name, int value);
    void insert(Header::Name name, size_t value);
    void insert(Header::Name name, const QUrl& value);
    void insert(Header::Name name, const QList<QByteArray>& values);
    void insert(const QByteArray& name, const QByteArray& value);
    void insert(const QByteArray& name, int value);
    void insert(const QByteArray& name, size_t value);
    void insert(const QByteArray& name, const QUrl& value);
    void insert(const QByteArray& name, const QList<QByteArray>& values);

    /**
     * @brief Removes all the entries that have the @p key
     */
    int remove(const Header& header);
    int remove(Header::Name name);
    int remove(Header::Name name, const QByteArray& value);
    int remove(Header::Name name, int value);
    int remove(Header::Name name, size_t value);
    int remove(Header::Name name, const QUrl& value);
    int remove(const QByteArray& name);
    int remove(const QByteArray& name, const QByteArray& value);
    int remove(const QByteArray& name, int value);
    int remove(const QByteArray& name, size_t value);
    int remove(const QByteArray& name, const QUrl& value);

    //    void replace(const Header &replacement);
    //    void replace(Header::Name name, const QByteArray &replacement);
    //    void replace(Header::Name name, const QByteArray &replacement);
    //    void replace(Header::Name name, int replacement);
    //    void replace(Header::Name name, size_t replacement);
    //    void replace(Header::Name name, const QUrl &replacement);
    //    void replace(const QByteArray &name, const QByteArray &replacement);
    //    void replace(const QByteArray &name, int replacement);
    //    void replace(const QByteArray &name, size_t replacement);
    //    void replace(const QByteArray &name, const QUrl &replacement);

    //
    // --- HELPER METHODS ---------------------------------------------------------------
    //

    /**
     * Returns the first "Accept" header value
     */
    QByteArray accept() const
    {
        return header(Header::Name::Accept).value();
    }

    /**
     * Returns the first "Accept-Encoding" header value
     */
    QByteArray acceptEncoding() const
    {
        return header(Header::Name::AcceptEncoding).value();
    }

    /**
     * Returns the first "Authorization" header value
     */
    QByteArray authorization() const
    {
        return header(Header::Name::Authorization).value();
    }

    /**
     * Returns all "Authorization" header values
     */
    QList<QByteArray> authorizationList() const
    {
        return header(Header::Name::Authorization).values();
    }

    /**
     * Returns the first "Cache-Control" header value
     */
    QByteArray cacheControl() const
    {
        return header(Header::Name::CacheControl).value();
    }

    /**
     * Returns the first "Content-Encoding" header value
     */
    QByteArray contentEncoding() const
    {
        return header(Header::Name::ContentEncoding).value();
    }

    /**
     * Returns all "Content-Encoding" header values
     */
    QList<QByteArray> contentEncodingList() const
    {
        return header(Header::Name::ContentEncoding).values();
    }

    /**
     * Returns the first "Content-Length" header value
     */
    QByteArray contentLength() const
    {
        return header(Header::Name::ContentLength).value();
    }

    /**
     * Returns the first "Content-MD5" header value
     */
    QByteArray contentMF5() const
    {
        return header(Header::Name::ContentMd5).value();
    }

    /**
     * Returns the first "Content-Range" header value
     */
    QByteArray contentRange() const
    {
        return header(Header::Name::ContentRange).value();
    }

    /**
     * Returns the first "Content-Type" header value
     */
    QByteArray contentType() const
    {
        return header(Header::Name::ContentType).value();
    }

    void setContentType(const QByteArray& contentType)
    {
        insert(Header::Name::ContentType, contentType);
    }

    void setContentType(const QString& contentType)
    {
        setContentType(contentType.toLatin1());
    }

    /**
     * Returns the first "Cookie" header value
     */
    QByteArray cookie() const
    {
        return header(Header::Name::Cookie).value();
    }

    /**
     * Returns the first "Date" header value
     */
    QByteArray date() const
    {
        return header(Header::Name::Date).value();
    }

    /**
     * Returns the first "ETag" header value
     */
    QByteArray eTag() const
    {
        return header(Header::Name::ETag).value();
    }

    /**
     * Returns the first "Expires" header value
     */
    QByteArray expires() const
    {
        return header(Header::Name::Expires).value();
    }

    /**
     * Returns the first "If-Match" header value
     */
    QByteArray ifMatch() const
    {
        return header(Header::Name::IfMatch).value();
    }

    /**
     * Returns the first "If-None-Match" header value
     */
    QByteArray ifNoneMatch() const
    {
        return header(Header::Name::IfNoneMatch).value();
    }

    /**
     * Returns the first "If-Modified-Since" header value
     */
    QByteArray ifModifiedSince() const
    {
        return header(Header::Name::IfModifiedSince).value();
    }

    /**
     * Returns the first "If-Unmodified-Since" header value
     */
    QByteArray ifUnmodifiedSince() const
    {
        return header(Header::Name::IfUnmodifiedSince).value();
    }

    /**
     * Returns the first "If-Range" header value
     */
    QByteArray ifRange() const
    {
        return header(Header::Name::IfRange).value();
    }

    /**
     * Returns the first "Last-Modified" header value
     */
    QByteArray lastModified() const
    {
        return header(Header::Name::LastModified).value();
    }

    /**
     * Returns the first "Location" header value
     */
    QByteArray location() const
    {
        return header(Header::Name::Location).value();
    }

    /**
     * Returns the first "Range" header value
     */
    QByteArray range() const
    {
        return header(Header::Name::Range).value();
    }

    /**
     * Returns the first "Retry-After" header value
     */
    QByteArray retryAfter() const
    {
        return header(Header::Name::RetryAfter).value();
    }

    /**
     * Returns the first "User-Agent" header value
     */
    QByteArray userAgent() const
    {
        return header(Header::Name::UserAgent).value();
    }

    /**
     * Returns the first "Age" header value
     */
    QByteArray age() const
    {
        return header(Header::Name::Age).value();
    }

protected:
    QList<Header> m_headers;
};

FLUGS_END_NAMESPACE

#endif
