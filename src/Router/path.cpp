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
#include "path.h"

FLUGS_USE_NAMESPACE

#if 0
struct Node
{
    PathSegment pathSegment;
    QPointer<Route> route = nullptr;
    QList<Node*> children;

    Node* match(const QString &requestPath, QHash<QString, QVariant> &params)
    {
        return match(requestPath.split('/'), params);
    }

    Node* match(QStringList requestPathList, QHash<QString, QVariant> &params)
    {
        if(!pathSegment.isEmpty()) {
            if(requestPathList.isEmpty()) {
                return nullptr;
            }

            QString requestPath = requestPathList.takeFirst();
            if(pathSegment.isFixed()) {
                if(pathSegment.name().compare(requestPath, pathSegment.cs()) != 0) {
                    return nullptr;
                }
            }
            else {
                if(params.contains(pathSegment.name())) {
                    qDebug() << "Path parameter name" << pathSegment.name() << "already used."; ///FIXME
                    return nullptr;
                }

                if(pathSegment.isWildcard()) {
                    Q_ASSERT(children.isEmpty());

                    if(!requestPathList.isEmpty()) {
                        requestPath.append("/" + requestPathList.join('/'));
                    }
                    params.insert(pathSegment.name(), requestPath);
                }
                else if(pathSegment.isOptional()) {
                    //FIXME
                    Q_ASSERT_X(false, "Optional", "Case not implemented!");
                    return nullptr;
                }
                else if(!pathSegment.validator()) {
                    if(!pathSegment.validator()(pathSegment.name(), requestPath)) {
                        return nullptr;
                    }

                    params.insert(pathSegment.name(), requestPath);
                }
                else {
                    return nullptr;
                }
            }
        }

        if(requestPathList.isEmpty()) {
            return this;
        }

        for(Node *node : children) {
            Q_ASSERT(node);
            if(node->match(requestPathList, params) != nullptr) {
                return node;
            }
        }

        return nullptr;
    }
};
#endif


Path::Path(const QString &str)
{
    if(str.startsWith(QChar::fromLatin1('{')) && str.endsWith(QChar::fromLatin1('}'))) {
        QString var = str.mid(1, str.length() - 2);
        m_fixed = false;

        if(var.startsWith(QChar::fromLatin1('*'))) {
            m_wildcard = true;
            var = str.mid(1, str.length() - 2);
        }
        else if(var.startsWith(QChar::fromLatin1('?'))) {
            m_optional = true;
            var = str.mid(1, str.length() - 2);
        }

        if(var.contains(QChar::fromLatin1(':'))) {
            int idx = var.indexOf(QChar::fromLatin1(':'));
            m_validatorName = var.mid(idx + 1);

            if(!m_validatorName.isEmpty()) {
                m_name = var.mid(0, idx);
            }
            else {
                qDebug() << "Invalid validator for path segment" << var;
            }
        }
        else if(var.contains(QChar::fromLatin1('~'))) {
            int idx = var.indexOf(QChar::fromLatin1('~'));
            QString name = var.mid(0, idx);
            QString pattern = var.mid(idx + 1);

            if(!pattern.isEmpty()) {
                QRegularExpression re(pattern);
                if(!pattern.isEmpty() && re.isValid()) {
                    m_name = name;
                    m_regex = re;
                }
                else {
                    qDebug().nospace() << "Invalid regular expression " << pattern << ":" << re.errorString();
                }
            }
            else {
                qDebug() << "Empty regular expression:" << str;
            }
        }
    }
    else {
        m_fixed = true;
        m_name = str;
    }
}

