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
#ifndef FLUGS_FOUNDATION_GLOBAL_H
#define FLUGS_FOUNDATION_GLOBAL_H

/**
 * @defgroup Flugs
 * @brief A lightweight HTTP/HTTPS server library.
 */

#include "flugs_foundation_export.h"

#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QVersionNumber>
#include <QtCore/QtGlobal>

#include <QtCore/QDebug>
#include <QtCore/QLoggingCategory>

#include <QtNetwork/QHostAddress>

#include <functional>

#define FLUGS_WIP 0

// clang-format off
#define FLUGS_BEGIN_NAMESPACE namespace Flugs {
#define FLUGS_END_NAMESPACE }
// clang-format on

#define FLUGS_USE_NAMESPACE using namespace Flugs;
#define FLUGS_NAMESPACED(CLASS) Flugs::##CLASS
#define FLUGS_NAMESPACE_PREFIX Flugs::

#define FLUGS_ROOT_LOGGING_CATEGORY "Flugs"

FLUGS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(Log)
Q_DECLARE_LOGGING_CATEGORY(LogParser)

FLUGS_END_NAMESPACE

#endif
