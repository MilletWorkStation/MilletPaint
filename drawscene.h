#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include "gridtool.h"
#include "AlignType.h"

#include <QGraphicsScene>


class DrawScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DrawScene(QObject *parent = 0);
    ~DrawScene();
    void setView(QGraphicsView * view ) { m_view = view ; }
    QGraphicsView * view() { return m_view; }

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    QGraphicsView * m_view;
    double m_dx, m_dy;
    bool m_bMoved;
    GridTool * m_pGrid;

};

#endif // DRAWSCENE_H
