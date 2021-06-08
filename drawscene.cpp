#include "drawscene.h"
#include "drawtool.h"
#include<QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

DrawScene::DrawScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_pGrid(nullptr)
{
    m_dx=m_dy=0;
    m_pGrid = new GridTool();
    QGraphicsItem * item = addRect(QRectF(0,0,0,0));

    // 图形项可以接收悬停事件
    item->setAcceptHoverEvents(true);
}

DrawScene::~DrawScene()
{
    delete m_pGrid;
}

void DrawScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter,rect);
    painter->fillRect(sceneRect(),Qt::white);
    if( m_pGrid ){
        m_pGrid->paintGrid(painter, sceneRect());
    }

}

void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DrawTool * pTool = DrawTool::findTool(DrawTool::c_drawShape);
    if( pTool != nullptr)
        pTool->mousePressEvent(event, this);
}

void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    DrawTool * pTool = DrawTool::findTool(DrawTool::c_drawShape);
    if( pTool != nullptr)
        pTool->mouseMoveEvent(event, this);
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DrawTool * pTool = DrawTool::findTool(DrawTool::c_drawShape);
    if( pTool != nullptr)
        pTool->mouseReleaseEvent(event, this);
}

