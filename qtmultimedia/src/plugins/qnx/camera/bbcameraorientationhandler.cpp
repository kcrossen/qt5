/****************************************************************************
**
** Copyright (C) 2013 Research In Motion
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bbcameraorientationhandler.h"

#include <QAbstractEventDispatcher>
#include <QCoreApplication>
#include <QDebug>

#include <bps/orientation.h>

QT_BEGIN_NAMESPACE

BbCameraOrientationHandler::BbCameraOrientationHandler(QObject *parent)
    : QObject(parent)
    , m_orientation(0)
{
    QCoreApplication::eventDispatcher()->installNativeEventFilter(this);
    int result = orientation_request_events(0);
    if (result == BPS_FAILURE)
        qWarning() << "Unable to register for orientation change events";

    orientation_direction_t direction = ORIENTATION_FACE_UP;
    int angle = 0;

    result = orientation_get(&direction, &angle);
    if (result == BPS_FAILURE) {
        qWarning() << "Unable to retrieve initial orientation";
    } else {
        m_orientation = angle;
    }
}

BbCameraOrientationHandler::~BbCameraOrientationHandler()
{
#ifndef Q_OS_BLACKBERRY_TABLET
    const int result = orientation_stop_events(0);
    if (result == BPS_FAILURE)
        qWarning() << "Unable to unregister for orientation change events";
#endif

    QCoreApplication::eventDispatcher()->removeNativeEventFilter(this);
}

bool BbCameraOrientationHandler::nativeEventFilter(const QByteArray&, void *message, long*)
{
    bps_event_t* const event = static_cast<bps_event_t*>(message);
    if (!event || bps_event_get_domain(event) != orientation_get_domain())
        return false;

    const int angle = orientation_event_get_angle(event);
    if (angle != m_orientation) {
        m_orientation = angle;
        emit orientationChanged(m_orientation);
    }

    return false; // do not drop the event
}

int BbCameraOrientationHandler::orientation() const
{
    return m_orientation;
}

QT_END_NAMESPACE
