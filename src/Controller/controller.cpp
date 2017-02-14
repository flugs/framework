/****************************************************************************
**
** This file is part of Flugs.
**
** Copyright 2017 Stefan Böhmann <sboehmann@flugs.io>
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
#include "controller.h"

#include <Flugs/Foundation/StringUtils>

#include <QMetaClassInfo>

FLUGS_USE_NAMESPACE

Controller::Controller(QObject* parent)
    : QObject(parent)
{
}

Controller::~Controller()
{
}

QString Controller::basePath() const
{
    if (!m_basePath.isEmpty()) {
        return m_basePath;
    }

    // Controller path from Class Name
    QString path = StringUtils::removeSuffix(QString::fromLatin1(metaObject()->className()), QStringLiteral("Controller"), Qt::CaseInsensitive);

    // Try to find the FLUGS_CONTROLLER_BASE_PATH annotation
    for (int i = metaObject()->classInfoOffset(); i < metaObject()->classInfoCount(); ++i) {
        auto info = metaObject()->classInfo(i);

        QString name = QString::fromLatin1(info.name());
        if (name == QStringLiteral("FLUGS_CONTROLLER_BASE_PATH")) {
            path = QString::fromLatin1(info.value()).trimmed();
            break;
        }
    }

    // ensure that an non empty path starts but does not end with /
    const QChar ch = QChar::fromLatin1('/');
    if (!path.startsWith(ch)) {
        path.prepend(ch);
    }

    while (path.endsWith(ch)) {
        path = path.remove(path.size() - 1, 1).trimmed();
    }

    return path;
}

void Controller::setBasePath(const QString& path)
{
    m_basePath = path.trimmed();

    if (!m_basePath.isEmpty()) {
        const QChar ch = QChar::fromLatin1('/');

        if (!m_basePath.startsWith(ch)) {
            m_basePath.prepend(ch);
        }

        while (m_basePath.endsWith(ch)) {
            m_basePath = m_basePath.remove(m_basePath.size() - 1, 1).trimmed();
        }
    }
}
