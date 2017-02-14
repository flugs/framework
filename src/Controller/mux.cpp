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
#include "mux.h"

#include <Flugs/Foundation/StringUtils>

#include <QDebug>
#include <QMetaClassInfo>

#include <functional>

FLUGS_USE_NAMESPACE

QVector<RouterAddFn> getMapHandlerFunctions(const QString& methodName, QString& value)
{
    auto removePrefixIfExists = [&](const QString& method) {
        if (value.startsWith(method)) {
            value = StringUtils::removePrefix(value, method);
            return true;
        }

        return false;
    };

    QVector<RouterAddFn> handlers;
    do {
        if (removePrefixIfExists(QStringLiteral("GET"))) {
            handlers.append(&Router::get);
            continue;
        }
        if (removePrefixIfExists(QStringLiteral("POST"))) {
            handlers.append(&Router::post);
            continue;
        }
        if (removePrefixIfExists(QStringLiteral("PUT"))) {
            handlers.append(&Router::put);
            continue;
        }
        if (removePrefixIfExists(QStringLiteral("HEAD"))) {
            handlers.append(&Router::head);
            continue;
        }
        if (removePrefixIfExists(QStringLiteral("DELETE"))) {
            handlers.append(&Router::del);
            continue;
        }
        if (removePrefixIfExists(QStringLiteral("OPTIONS"))) {
            handlers.append(&Router::options);
            continue;
        }
        if (removePrefixIfExists(QStringLiteral("PATCH"))) {
            handlers.append(&Router::patch);
            continue;
        }

        break;
    } while (true);

    if (handlers.isEmpty()) {
        if (methodName.startsWith(QStringLiteral("get"), Qt::CaseInsensitive)) {
            handlers.append(&Router::get);
        }
        else if (methodName.startsWith(QStringLiteral("put"), Qt::CaseInsensitive)) {
            handlers.append(&Router::put);
        }
        else if (methodName.startsWith(QStringLiteral("post"), Qt::CaseInsensitive)) {
            handlers.append(&Router::put);
        }
        else if (methodName.startsWith(QStringLiteral("head"), Qt::CaseInsensitive)) {
            handlers.append(&Router::head);
        }
        else if (methodName.startsWith(QStringLiteral("delete"), Qt::CaseInsensitive) || methodName.startsWith(QStringLiteral("remove"), Qt::CaseInsensitive)) {
            handlers.append(&Router::del);
        }
        else if (methodName.startsWith(QStringLiteral("patch"), Qt::CaseInsensitive)) {
            handlers.append(&Router::patch);
        }
        else {
            handlers.append(&Router::get);
            handlers.append(&Router::post);
            handlers.append(&Router::put);
        }
    }

    return handlers;
}

Mux::Mux(QObject* parent)
    : QObject(parent)
{
}

Mux::Mux(Server* server, QObject* parent)
    : QObject(parent)
{
    m_router.serve(server);
}

Mux::~Mux()
{
}

void Mux::serve(Server* server)
{
    m_router.serve(server);
}

void Mux::addController(Controller* ctrl)
{
    auto m = ctrl->metaObject();
    const QString className = QString::fromLatin1(m->className());

    for (int i = m->classInfoOffset(); i < m->classInfoCount(); ++i) {
        auto info = m->classInfo(i);
        QString methodName = QString::fromLatin1(info.name()); /// TODO change to QByteArray?
        if (!methodName.startsWith(QStringLiteral("FLUGS_MAP_"))) {
            continue;
        }

        methodName = StringUtils::removePrefix(methodName, QStringLiteral("FLUGS_MAP_"));
        QString value = QString::fromLatin1(info.value()); /// TODO change to QByteArray?
        QVector<RouterAddFn> handlers = getMapHandlerFunctions(methodName, value);

        for (int k = m->methodOffset(); k < m->methodCount(); ++k) {
            QMetaMethod method = m->method(k);
            registerControllerMethodByName(className, methodName, method, handlers);
        }

        auto basePath = ctrl->basePath();

        qDebug() << "basePath:" << basePath;

        qDebug() << methodName << ":" << value;
    }
}

void Mux::removeController(Controller* ctrl)
{
}

bool Mux::registerControllerMethodByName(const QString& className, const QString& methodName, const QMetaMethod& method, QVector<RouterAddFn> handlers)
{
    if (method.methodType() == QMetaMethod::Constructor) {
        return false;
    }

    if (method.name() != methodName.toLatin1()) {
        return false;
    }

    int returnType = method.returnType();

    if (returnType == QMetaType::UnknownType) {
        qWarning().nospace().noquote() << "Unknown return type for " << className << "::" << method.name() << ". "
                                       << "See https://doc.flugs.io/controller/return_type for more informations.";

        return false;
    }

    auto h = [=](Request req, Response* res) {

    };

    foreach (auto handlerFn, handlers) {
        ((m_router).*(handlerFn))(QStringLiteral("path"), h);
    }

    return true;
}
