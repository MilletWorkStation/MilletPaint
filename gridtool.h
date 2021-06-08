#ifndef GRIDTOOL_H
#define GRIDTOOL_H

#include <QPainter>
#include <QSize>

class GridTool
{
public:
    GridTool(const QSize &grid = QSize(3200,2400) , const QSize & space = QSize(20,20) );
    void paintGrid(QPainter *painter,const QRectF & rect );
protected:
    QSize m_sizeGrid;
    QSize m_sizeGridSpace;
};

#endif // GRIDTOOL_H
