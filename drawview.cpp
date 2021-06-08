#include "drawview.h"

DrawView::DrawView(QGraphicsScene *scene)
   : QGraphicsView(scene)
{

    //这是激活整个窗体的鼠标追踪， 默认需要按下鼠标左键才能激活 mouseMoveEvent
    setMouseTracking(true);

    // 窗体的刻度尺
    // 这里第三个参数一定要传入，因为是在本界面上显示绘制
    m_pHRuleBar = new QtRuleBar(Qt::Horizontal, this, this);
    m_pVRuleBar = new QtRuleBar(Qt::Vertical, this, this);

    setViewport(new QWidget);
    setAttribute(Qt::WA_DeleteOnClose);

    // 设置边距，标尺的宽高
    setViewportMargins(RULER_SIZE-1,RULER_SIZE-1,0,0);

    // 首次进入，新建一个
    NewFile();
}

void DrawView::zoomIn()
{
    scale(1.2, 1.2);
    updateRuler();
}

void DrawView::zoomOut()
{
    scale(1 / 1.2, 1 / 1.2);
    updateRuler();
}

void DrawView::NewFile()
{
    static int sequenceNumber = 1;

    m_bIsUntitled = true;
    m_bModified = true;
    m_strCurFile = tr("Paint-%1.xml").arg(sequenceNumber++);
    setWindowTitle(m_strCurFile + "[*]");
}

bool DrawView::MaybeSave()
{
    if (m_bModified)
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("MDI"),
                                   tr("'%1' has been modified.\n"
                                      "Do you want to save your changes?")
                                       .arg(UserFriendlyCurrentFile()),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return Save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }

    return true;
}

bool DrawView::Save()
{
    return m_bIsUntitled ? SaveAs() : SaveFile(m_strCurFile);
}

bool DrawView::SaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), m_strCurFile);
    if (fileName.isEmpty())
        return false;

    return SaveFile(fileName);
}

bool DrawView::SaveFile(const QString &fileName)
{

}

bool DrawView::Load()
{

}

QString DrawView::StrippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();

}

QString DrawView::UserFriendlyCurrentFile()
{
    return StrippedName(m_strCurFile);
}

void DrawView::closeEvent(QCloseEvent *event)
{
    MaybeSave() ? event->accept() : event->ignore();
}

void DrawView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pt =mapToScene(event->pos());

    m_pHRuleBar->updatePosition(event->pos());
    m_pVRuleBar->updatePosition(event->pos());

    emit PositionChanged( pt.x() , pt.y() );
    QGraphicsView::mouseMoveEvent(event);
}

void DrawView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    m_pHRuleBar->resize( this->size().width()- RULER_SIZE - 1,RULER_SIZE);
    m_pHRuleBar->move( RULER_SIZE, 0);
    m_pVRuleBar->resize( RULER_SIZE, this->size().height() - RULER_SIZE - 1);
    m_pVRuleBar->move(0, RULER_SIZE);

    updateRuler();
}

void DrawView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx,dy);
    updateRuler();
}

void DrawView::updateRuler()
{
    if ( scene() == 0) return;

    // 获取当前窗体大小
    QRectF viewbox = this->rect();

    // 将场景左上角的值转换到视图左上角的值
    QPointF offset = mapFromScene( scene()->sceneRect().topLeft() );

    // 获取横向缩放的值
    // Returns the horizontal scaling factor.
    double factor =  1.0 / transform().m11();

    // 最小值 = 缩放比例 * (视口左边值 - 偏移的原点值)
    double lower_x = factor * ( viewbox.left()  - offset.x() );
    // 最小值 = 缩放比例 * (视口右边边值 - 标尺宽度 - 偏移的原点值)
    double upper_x = factor * ( viewbox.right() - RULER_SIZE - offset.x());

    // 设置横向的范围
    m_pHRuleBar->SetRange(lower_x, upper_x, upper_x - lower_x );

    // 更新重绘
    m_pHRuleBar->update();

    double lower_y = factor * ( viewbox.top() - offset.y()) * -1;
    double upper_y = factor * ( viewbox.bottom() - RULER_SIZE - offset.y() ) * -1;

    m_pVRuleBar->SetRange(lower_y, upper_y, upper_y - lower_y );
    m_pVRuleBar->update();

}
