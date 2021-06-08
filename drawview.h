#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QGraphicsView>
#include "qtrulebar.h"


class DrawView : public QGraphicsView
{
    Q_OBJECT

public:
    DrawView(QGraphicsScene *scene);

    // 缩放功能
    // void scale(qreal sx, qreal sy)
    void zoomIn();
    void zoomOut();

    void NewFile();
    bool MaybeSave();

    bool Save();
    bool SaveAs();
    bool SaveFile(const QString &fileName);
    bool Load();

    QString UserFriendlyCurrentFile();
    QString StrippedName(const QString &fullFileName);
signals:
    void PositionChanged(const int x ,const int y );
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void scrollContentsBy(int dx, int dy) Q_DECL_OVERRIDE;

protected:
    void updateRuler();

protected:
    QtRuleBar * m_pHRuleBar;
    QtRuleBar * m_pVRuleBar;

    QString m_strCurFile;
    bool m_bIsUntitled;
    bool m_bModified;
};

#endif // DRAWVIEW_H
