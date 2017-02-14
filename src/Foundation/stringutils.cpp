/*
 * Copyright (C) 2016 Stefan Böhmann
 */
#include "stringutils.h"

FLUGS_BEGIN_NAMESPACE

QString StringUtils::removePrefix(const QString& str, const QString& prefix, Qt::CaseSensitivity cs)
{
    if (str.startsWith(prefix, cs)) {
        return str.right(str.size() - prefix.size());
    }

    return str;
}

QString StringUtils::removeSuffix(const QString& str, const QString& suffix, Qt::CaseSensitivity cs)
{
    if (str.endsWith(suffix, cs)) {
        return str.left(str.size() - suffix.size());
    }

    return str;
}

QString StringUtils::capwords(const QString& text)
{
    if (text.isEmpty()) {
        return text;
    }

    QStringList words = text.split(QLatin1Char(' '));
    return capwords(words).join(QLatin1Char(' '));
}

QStringList StringUtils::capwords(const QStringList& list)
{
    QStringList tmp = list;
    for (auto it = tmp.begin(); it != tmp.end(); ++it) {
        if (!(*it).isEmpty()) {
            *it = (*it)[0].toUpper() + (*it).midRef(1);
        }
    }

    return tmp;
}

QString StringUtils::lsqueeze(const QString& str, int maxlen)
{
    if (str.size() > maxlen) {
        return QStringLiteral("...") + str.rightRef(maxlen - 3);
    }

    return str;
}

QString StringUtils::csqueeze(const QString& str, int maxlen)
{
    maxlen = qMax(3, maxlen);

    if (str.size() > maxlen) {
        const int part = (maxlen - 3) / 2;
        return str.leftRef(part) + QStringLiteral("...") + str.rightRef(part);
    }

    return str;
}

QString StringUtils::rsqueeze(const QString& str, int maxlen)
{
    if (str.size() > maxlen) {
        return str.leftRef(maxlen - 3) + QStringLiteral("...");
    }

    return str;
}

FLUGS_END_NAMESPACE
