#ifndef QTRULEBAR_H
#define QTRULEBAR_H

#include <QtWidgets>

#define RULER_SIZE    16

class QtRuleBar : public QWidget
{
    Q_OBJECT
public:
    explicit QtRuleBar(Qt::Orientation direction, QGraphicsView * view, QWidget * parent = 0  );
    void SetRange(const int nLower, const int nUpper, const int nMax);
    void updatePosition( const QPoint & pos );
protected:
    void paintEvent(QPaintEvent *event) ;

    // 绘制刻度线
    void DrawTicker(QPainter& painter);

    // 绘制鼠标当前位置
    void DrawPos(QPainter& painter) ;

protected:
    QPoint m_LastPos;
    QColor m_BackgroundColor;

    Qt::Orientation m_Orient;
    int m_nLower;
    int m_nUpper;
    int m_nMax;

};

#endif // QTRULEBAR_H
