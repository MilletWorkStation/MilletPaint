#ifndef DRAWTOOL_H
#define DRAWTOOL_H

#include "drawscene.h"

// 为了不包这么多头文件  影响编译效率
QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QAbstractGraphicsShapeItem;
QT_END_NAMESPACE

class DrawScene;
class QGraphicsItem;
class GraphicsPolygonItem;

// 图形类别
enum DrawShape
{
    DS_Selection ,
    DS_Rotation  ,

    DS_Line ,
    DS_Rectangle ,
    DS_Roundrect ,
    DS_Ellipse ,
    DS_Bezier,
    DS_Polygon,
    DS_Polyline,
};

// 绘制工具
class DrawTool
{
public:
    DrawTool( DrawShape shape );
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event ,DrawScene *scene );

    DrawShape m_drawShape;
    bool m_hoverSizer;

    static DrawTool * findTool( DrawShape drawShape );
    static QList<DrawTool*> c_tools;
    static QPointF c_down;
    static quint32 c_nDownFlags;
    static QPointF c_last;
    static DrawShape c_drawShape;

};

class SelectTool : public DrawTool
{
public:
    SelectTool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    QPointF initialPositions;
    QPointF opposite_;
    QGraphicsPathItem * dashRect;
};

class  RotationTool : public DrawTool
{
public:
    RotationTool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    qreal lastAngle;
    QGraphicsPathItem * dashRect;
};

class LineTool : public DrawTool
{
public:
    LineTool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    QGraphicsLineItem *m_pItem;
};


class RectTool : public DrawTool
{
public:
    RectTool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    QGraphicsItem * item;
};

class PolygonTool : public DrawTool
{
public:
    PolygonTool(DrawShape shape );
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event ,DrawScene *scene );
    GraphicsPolygonItem * item;
    int m_nPoints;
    QPointF initialPositions;

};

#endif // DRAWTOOL_H
