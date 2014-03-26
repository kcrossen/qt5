/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtLocation module of the Qt Toolkit.
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

#ifndef QDECLARATIVERECTANGLEMAPITEM_H_
#define QDECLARATIVERECTANGLEMAPITEM_H_

#include "qdeclarativegeomapitembase_p.h"
#include "qgeomapitemgeometry_p.h"
#include "qdeclarativepolylinemapitem_p.h"
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

QT_BEGIN_NAMESPACE

class QGeoMapRectangleGeometry : public QGeoMapItemGeometry
{
    Q_OBJECT

public:
    explicit QGeoMapRectangleGeometry(QObject *parent = 0);

    void updatePoints(const QGeoMap &map,
                      const QGeoCoordinate &topLeft,
                      const QGeoCoordinate &bottomRight);
};

class MapRectangleNode;

class QDeclarativeRectangleMapItem: public QDeclarativeGeoMapItemBase
{
    Q_OBJECT

    Q_PROPERTY(QGeoCoordinate topLeft READ topLeft WRITE setTopLeft NOTIFY topLeftChanged)
    Q_PROPERTY(QGeoCoordinate bottomRight READ bottomRight WRITE setBottomRight NOTIFY bottomRightChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QDeclarativeMapLineProperties *border READ border)

public:
    explicit QDeclarativeRectangleMapItem(QQuickItem *parent = 0);
    ~QDeclarativeRectangleMapItem();

    virtual void setMap(QDeclarativeGeoMap *quickMap, QGeoMap *map);
    //from QuickItem
    virtual QSGNode *updateMapItemPaintNode(QSGNode *, UpdatePaintNodeData *);

    QGeoCoordinate topLeft();
    void setTopLeft(const QGeoCoordinate &center);

    QGeoCoordinate bottomRight();
    void setBottomRight(const QGeoCoordinate &center);

    QColor color() const;
    void setColor(const QColor &color);

    QDeclarativeMapLineProperties *border();

    void dragStarted();
    void dragEnded();
    bool contains(const QPointF &point) const;

Q_SIGNALS:
    void topLeftChanged(const QGeoCoordinate &topLeft);
    void bottomRightChanged(const QGeoCoordinate &bottomRight);
    void colorChanged(const QColor &color);

protected Q_SLOTS:
    virtual void updateMapItem();
    void updateMapItemAssumeDirty();
    void afterViewportChanged(const QGeoMapViewportChangeEvent &event);

private:
    QGeoCoordinate topLeft_;
    QGeoCoordinate bottomRight_;
    QDeclarativeMapLineProperties border_;
    QColor color_;
    bool dirtyMaterial_;
    QGeoMapRectangleGeometry geometry_;
    QGeoMapPolylineGeometry borderGeometry_;
};

//////////////////////////////////////////////////////////////////////

QT_END_NAMESPACE

QML_DECLARE_TYPE(QDeclarativeRectangleMapItem)

#endif /* QDECLARATIVERECTANGLEMAPITEM_H_ */
