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
#ifndef FLUGS_FOUNDATION_STRINGUTILS_H
#define FLUGS_FOUNDATION_STRINGUTILS_H

#include <Flugs/Foundation/Global>

#include <QtCore/QString>
#include <QtCore/QStringList>

FLUGS_BEGIN_NAMESPACE

/**
 * @ingroup Core
 */
namespace StringUtils
{
QString FLUGS_FOUNDATION_EXPORT removePrefix(const QString& str, const QString& prefix, Qt::CaseSensitivity cs = Qt::CaseSensitive);

QString FLUGS_FOUNDATION_EXPORT removeSuffix(const QString& str, const QString& suffix, Qt::CaseSensitivity cs = Qt::CaseSensitive);

/**
 * @brief Capitalizes each word in the string "a sunny day" becomes "A Sunny Day".
 *
 * @param text the text to capitalize
 * @return the resulting string
 */
QString FLUGS_FOUNDATION_EXPORT capwords(const QString& text);

/**
 * @brief Capitalizes each word in the list [hello, there] becomes [Hello, There]
 *
 * @param list the list to capitalize
 * @return the resulting list
 */
QStringList FLUGS_FOUNDATION_EXPORT capwords(const QStringList& list);

/**
 * @brief Substitute characters at the beginning of a string by "...".
 *
 * If the original string is shorter than "maxlen", it is returned verbatim.
 *
 * @param str is the string to modify
 * @param maxlen is the maximum length the modified string will have
 *
 * @return the modified string
 */
QString FLUGS_FOUNDATION_EXPORT lsqueeze(const QString& str, int maxlen = 40);

/**
 * @brief Substitute characters at the middle of a string by "...".
 *
 * If the original string is shorter than "maxlen", it is returned verbatim
 *
 * @param str is the string to modify
 * @param maxlen is the maximum length the modified string will have
 *
 * @return the modified string
 */
QString FLUGS_FOUNDATION_EXPORT csqueeze(const QString& str, int maxlen = 40);

/**
 * @brief Substitute characters at the end of a string by "...".
 *
 * If the original string is shorter than "maxlen", it is returned verbatim
 *
 * @param str is the string to modify
 * @param maxlen is the maximum length the modified string will have
 *
 * @return the modified string
 */
QString FLUGS_FOUNDATION_EXPORT rsqueeze(const QString& str, int maxlen = 40);
}

FLUGS_END_NAMESPACE

#endif
