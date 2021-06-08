#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawview.h"

#include <QMainWindow>

#include <QAction>
#include <QMdiArea>
#include <QToolBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void CreateAction();
    void CreateMenuBar();
    void CreateToolBar();
    void CreateStatusBar();

    /// 创建新的子窗体
    DrawView* CreateMdiChild();

    ///
    QMdiArea *m_pMdiArea;

    /// MenuAction
    // File
    QAction * m_pFileNew;
    QAction * m_pFileOpen;
    QAction * m_pFileSave;
    QAction * m_pFileQuit;

    // Edit
    QAction * m_pEditUndo;
    QAction * m_pEditRedo;
    QAction * m_pEditCut;
    QAction * m_pEditCopy;
    QAction * m_pEditPaste;
    QAction * m_pEditDelete;

    // View
    QAction * m_pViewZoomIn;
    QAction * m_pViewZoomOut;

    // tools
        // shape
    QAction * m_pToolsShapeSelect;
    QAction * m_pToolsShapeLine;
    QAction * m_pToolsShapeRect;
    QAction * m_pToolsShapeRoundRect;
    QAction * m_pToolsShapeEllipse;
    QAction * m_pToolsShapePolygon;
    QAction * m_pToolsShapePolyline;
    QAction * m_pToolsShapeBezier;
    QAction * m_pToolsShapeRotate;

        // Align
    QAction * m_pToolsAlignRight;
    QAction * m_pToolsAlignLeft;
    QAction * m_pToolsAlignHCenter;
    QAction * m_pToolsAlignVCenter;
    QAction * m_pToolsAlignTop;
    QAction * m_pToolsAlignBottom;
    QAction * m_pToolsAlignHorizontal;
    QAction * m_pToolsAlignVertical;
    QAction * m_pToolsAlignHeight;
    QAction * m_pToolsAlignWidth;
    QAction * m_pToolsAlignWidthAndHeight;

    // window
    QMenu   * m_pWindowMenu;
    QAction * m_pWindowClose;
    QAction * m_pWindowCloseAll;
    QAction * m_pWindowTitle;
    QAction * m_pWindowCascade;
    QAction * m_pWindowNext;
    QAction * m_pWindowPrevious;

    // help
    QAction * m_pHelpAbout;
    QAction * m_pHelpAboutQt;
    QAction * m_pHelpFuncTest;

    // Edit toolbar;
    QToolBar * m_pEditToolBar;
    // View toolbar;
    QToolBar * m_pViewToolBar;
    // Draw toolbar;
    QToolBar * m_pShapeToolBar;
    // Align toolbar;
    QToolBar * m_pAlignToolBar;

private slots:
    void Open();
    void New();
    void Save();
    void Quit();

    void ZoomIn();
    void ZoomOut();

    void PositionChanged(const int x, const int y);

    void AddShape();

public:
    DrawView * m_pView;

};
#endif // MAINWINDOW_H
