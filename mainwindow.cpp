#include "drawscene.h"
#include "drawtool.h"
#include "drawview.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>
#include <QMessageBox>
#include <QSignalMapper>

#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QDockWidget *dock = new QDockWidget(this);
//    addDockWidget(Qt::RightDockWidgetArea, dock);

    m_pMdiArea = new QMdiArea(this);
    m_pMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(m_pMdiArea);

    setWindowTitle(tr("Millet Paint"));

    CreateMenuBar();
    CreateToolBar();

    New();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateAction()
{
    m_pFileNew = new QAction("&New", this);
    m_pFileNew->setShortcut(QKeySequence::New);
    m_pFileNew->setStatusTip("Create a new file");
    connect(m_pFileNew, SIGNAL(triggered()), this, SLOT(New()));

    m_pFileOpen = new QAction("&Open", this);
    m_pFileOpen->setShortcut(QKeySequence::Open);
    m_pFileOpen->setStatusTip("Open file");
    connect(m_pFileOpen, SIGNAL(triggered()), this, SLOT(Open()));

    m_pFileSave = new QAction("&Save", this);
    m_pFileSave->setShortcut(QKeySequence::Save);
    m_pFileSave->setStatusTip("Save file");
    m_pFileSave->setEnabled(false);
    connect(m_pFileSave, SIGNAL(triggered()), this, SLOT(Save()));

    m_pFileQuit = new QAction("&Quit", this);
    m_pFileQuit->setShortcut(QKeySequence::Quit);
    m_pFileQuit->setStatusTip("Quit App");
    connect(m_pFileQuit, SIGNAL(triggered()), this, SLOT(Quit()));

    // Edit
    m_pEditUndo = new QAction("&Undo", this);
    m_pEditUndo->setShortcut(QKeySequence::Undo);
    m_pEditUndo->setStatusTip("Undo");
    m_pEditUndo->setEnabled(false);
    m_pEditUndo->setIcon(QIcon(":icons/undo.png"));

    m_pEditRedo = new QAction("&Redo", this);
    m_pEditRedo->setShortcut(QKeySequence::Redo);
    m_pEditRedo->setStatusTip("Redo");
    m_pEditRedo->setEnabled(false);
    m_pEditRedo->setIcon(QIcon(":icons/redo.png"));

    m_pEditCut = new QAction("&Cut", this);
    m_pEditCut->setShortcut(QKeySequence::Cut);
    m_pEditCut->setStatusTip("Cut");
    m_pEditCut->setEnabled(false);
    m_pEditCut->setIcon(QIcon(":icons/cut.png"));

    m_pEditCopy = new QAction("&Copy", this);
    m_pEditCopy->setShortcut(QKeySequence::Copy);
    m_pEditCopy->setStatusTip("Copy");
    m_pEditCopy->setEnabled(false);
    m_pEditCopy->setIcon(QIcon(":icons/copy.png"));

    m_pEditPaste = new QAction("&Paste", this);
    m_pEditPaste->setShortcut(QKeySequence::Paste);
    m_pEditPaste->setStatusTip("Paste");
    m_pEditPaste->setEnabled(false);
    m_pEditPaste->setIcon(QIcon(":icons/paste.png"));

    m_pEditDelete = new QAction("&Delete", this);
    m_pEditDelete->setShortcut(QKeySequence::Delete);
    m_pEditDelete->setStatusTip("Delete");
    m_pEditDelete->setEnabled(false);
    m_pEditDelete->setIcon(QIcon(":icons/delete.png"));

    // View
    m_pViewZoomIn = new QAction("&Zoom In", this);
    m_pViewZoomIn->setIcon(QIcon(":icons/zoomin.png"));
    connect(m_pViewZoomIn, SIGNAL(triggered()), this, SLOT(ZoomIn()));

    m_pViewZoomOut = new QAction("&Zoom Out", this);
    m_pViewZoomOut->setIcon(QIcon(":icons/zoomout.png"));
    connect(m_pViewZoomOut, SIGNAL(triggered()), this, SLOT(ZoomOut()));

    // tool
    m_pToolsShapeSelect = new QAction("&Select", this);
    m_pToolsShapeSelect->setIcon(QIcon(":icons/arrow.png"));

        // shape
        m_pToolsShapeLine = new QAction("&Line", this);
        m_pToolsShapeLine->setIcon(QIcon(":icons/line.png"));
        connect(m_pToolsShapeLine, SIGNAL(triggered()), this, SLOT(AddShape()));

        m_pToolsShapeRect = new QAction("&Rect", this);
        m_pToolsShapeRect->setIcon(QIcon(":icons/rectangle.png"));
        // 根据发送者去判定需要添加什么类型的图形
        connect(m_pToolsShapeRect, SIGNAL(triggered()), this, SLOT(AddShape()));

        m_pToolsShapeRoundRect = new QAction("&Round Rect", this);
        m_pToolsShapeRoundRect->setIcon(QIcon(":icons/roundrect.png"));
        connect(m_pToolsShapeRect, SIGNAL(triggered()), this, SLOT(AddShape()));

        m_pToolsShapeEllipse = new QAction("&Ellipse", this);
        m_pToolsShapeEllipse->setIcon(QIcon(":icons/ellipse.png"));
        connect(m_pToolsShapeEllipse, SIGNAL(triggered()), this, SLOT(AddShape()));

        m_pToolsShapePolygon = new QAction("&Ploygon", this);
        m_pToolsShapePolygon->setIcon(QIcon(":icons/polygon.png"));
        connect(m_pToolsShapePolygon, SIGNAL(triggered()), this, SLOT(AddShape()));

        m_pToolsShapePolyline = new QAction("&Polyline", this);
        m_pToolsShapePolyline->setIcon(QIcon(":icons/polyline.png"));
        connect(m_pToolsShapePolyline, SIGNAL(triggered()), this, SLOT(AddShape()));

        m_pToolsShapeBezier = new QAction("&Bezier", this);
        m_pToolsShapeBezier->setIcon(QIcon(":icons/bezier.png"));
        connect(m_pToolsShapeBezier, SIGNAL(triggered()), this, SLOT(AddShape()));

        m_pToolsShapeRotate = new QAction("&Rotate", this);
        m_pToolsShapeRotate->setIcon(QIcon(":icons/rotate.png"));
        connect(m_pToolsShapeRotate, SIGNAL(triggered()), this, SLOT(AddShape()));

        // align
        m_pToolsAlignRight = new QAction("&Right", this);
        m_pToolsAlignRight->setIcon(QIcon(":icons/align_right.png"));

        m_pToolsAlignLeft = new QAction("&Left", this);
        m_pToolsAlignLeft->setIcon(QIcon(":icons/align_left.png"));

        m_pToolsAlignHCenter = new QAction("&H Center", this);
        m_pToolsAlignHCenter->setIcon(QIcon(":icons/align_hcenter.png"));

        m_pToolsAlignVCenter = new QAction("&V Center", this);
        m_pToolsAlignVCenter->setIcon(QIcon(":icons/align_vcenter.png"));

        m_pToolsAlignTop = new QAction("&Top", this);
        m_pToolsAlignTop->setIcon(QIcon(":icons/align_top.png"));

        m_pToolsAlignBottom = new QAction("&Bottom", this);
        m_pToolsAlignBottom->setIcon(QIcon(":icons/align_bottom.png"));

        m_pToolsAlignHorizontal = new QAction("&Horizontal", this);
        m_pToolsAlignHorizontal->setIcon(QIcon(":icons/align_horzeven.png"));

        m_pToolsAlignVertical = new QAction("&Vertical", this);
        m_pToolsAlignVertical->setIcon(QIcon(":icons/align_verteven.png"));

        m_pToolsAlignHeight = new QAction("&Height", this);
        m_pToolsAlignHeight->setIcon(QIcon(":icons/align_height.png"));

        m_pToolsAlignWidth = new QAction("&Width", this);
        m_pToolsAlignWidth->setIcon(QIcon(":icons/align_width.png"));

        m_pToolsAlignWidthAndHeight = new QAction("&Width And Height", this);
        m_pToolsAlignWidthAndHeight->setIcon(QIcon(":icons/align_all.png"));

    // window
    m_pWindowClose = new QAction("&Close", this);
    m_pWindowCloseAll = new QAction("&Close All", this);
    m_pWindowTitle = new QAction("&Title", this);
    m_pWindowCascade = new QAction("&Cascade", this);
    m_pWindowNext = new QAction("&Next", this);
    m_pWindowPrevious = new QAction("&Previous", this);

    // help
    m_pHelpAbout = new QAction("&About", this);
    m_pHelpAboutQt = new QAction("&About Qt", this);
    m_pHelpFuncTest = new QAction("&Func Test", this);
}

void MainWindow::CreateMenuBar()
{
    CreateAction();

    QMenu * pMenu = nullptr;

    // File
    pMenu = new QMenu("&File", this);
    pMenu->addAction(m_pFileNew);
    pMenu->addAction(m_pFileOpen);
    pMenu->addAction(m_pFileSave);
    pMenu->addSeparator();
    pMenu->addAction(m_pFileQuit);
    ui->menubar->addMenu(pMenu);

    // Edit
    pMenu = new QMenu("&Edit", this);
    pMenu->addAction(m_pEditUndo);
    pMenu->addAction(m_pEditRedo);
    pMenu->addAction(m_pEditCut);
    pMenu->addAction(m_pEditCopy);
    pMenu->addAction(m_pEditPaste);
    pMenu->addAction(m_pEditDelete);
    ui->menubar->addMenu(pMenu);

    // View
    pMenu = new QMenu("&View", this);
    pMenu->addAction(m_pViewZoomIn);
    pMenu->addAction(m_pViewZoomOut);
    ui->menubar->addMenu(pMenu);

    // Tools
    pMenu = new QMenu("&Tools", this);
    pMenu->addAction(m_pToolsShapeSelect);

    QMenu * pShape = new QMenu("Shape", this);
    pShape->addAction(m_pToolsShapeLine);
    pShape->addAction(m_pToolsShapeRect);
    pShape->addAction(m_pToolsShapeRoundRect);
    pShape->addAction(m_pToolsShapeEllipse);
    pShape->addAction(m_pToolsShapePolygon);
    pShape->addAction(m_pToolsShapePolyline);
    pShape->addAction(m_pToolsShapeBezier);
    pShape->addAction(m_pToolsShapeRotate);
    pMenu->addMenu(pShape);

    QMenu * pAlign = new QMenu("Align", this);
    pAlign->addAction(m_pToolsAlignRight);
    pAlign->addAction(m_pToolsAlignLeft);
    pAlign->addAction(m_pToolsAlignHCenter);
    pAlign->addAction(m_pToolsAlignVCenter);
    pAlign->addAction(m_pToolsAlignTop);
    pAlign->addAction(m_pToolsAlignBottom);
    pAlign->addAction(m_pToolsAlignHorizontal);
    pAlign->addAction(m_pToolsAlignVertical);
    pAlign->addAction(m_pToolsAlignHeight);
    pAlign->addAction(m_pToolsAlignWidth);
    pAlign->addAction(m_pToolsAlignWidthAndHeight);
    pMenu->addMenu(pAlign);
    ui->menubar->addMenu(pMenu);

    pMenu = new QMenu("&Window", this);
    m_pWindowMenu = pMenu;
    pMenu->addAction(m_pWindowClose);
    pMenu->addAction(m_pWindowCloseAll);
    pMenu->addSeparator();
    pMenu->addAction(m_pWindowTitle);
    pMenu->addAction(m_pWindowCascade);
    pMenu->addSeparator();
    pMenu->addAction(m_pWindowNext);
    pMenu->addAction(m_pWindowPrevious);
    pMenu->addSeparator();
    ui->menubar->addMenu(pMenu);

    pMenu = new QMenu("&Help", this);
    pMenu->addAction(m_pHelpAbout);
    pMenu->addAction(m_pHelpAboutQt);
    pMenu->addAction(m_pHelpFuncTest);
    ui->menubar->addMenu(pMenu);
}

void MainWindow::CreateToolBar()
{
    // tool edit
    m_pEditToolBar = addToolBar("Edit");
    m_pEditToolBar->setIconSize(QSize(24, 24));
    m_pEditToolBar->addAction(m_pEditUndo);
    m_pEditToolBar->addAction(m_pEditRedo);
    m_pEditToolBar->addAction(m_pEditCut);
    m_pEditToolBar->addAction(m_pEditCopy);
    m_pEditToolBar->addAction(m_pEditPaste);

    // tool view
    m_pViewToolBar = addToolBar("View");
    m_pViewToolBar->addAction(m_pViewZoomIn);
    m_pViewToolBar->addAction(m_pViewZoomOut);

    // tool-Shape
    m_pShapeToolBar = addToolBar("Shape");
    m_pShapeToolBar->setIconSize(QSize(24, 24));
    m_pShapeToolBar->addAction(m_pToolsShapeSelect);
    m_pShapeToolBar->addAction(m_pToolsShapeLine);
    m_pShapeToolBar->addAction(m_pToolsShapeRect);
    m_pShapeToolBar->addAction(m_pToolsShapeRoundRect);
    m_pShapeToolBar->addAction(m_pToolsShapeEllipse);
    m_pShapeToolBar->addAction(m_pToolsShapePolygon);
    m_pShapeToolBar->addAction(m_pToolsShapePolyline);
    m_pShapeToolBar->addAction(m_pToolsShapeBezier);
    m_pShapeToolBar->addAction(m_pToolsShapeRotate);

    // tool-align
    m_pAlignToolBar = addToolBar("Align");
    m_pAlignToolBar->setIconSize(QSize(24, 24));
    m_pAlignToolBar->addAction(m_pToolsAlignRight);
    m_pAlignToolBar->addAction(m_pToolsAlignLeft);
    m_pAlignToolBar->addAction(m_pToolsAlignHCenter);
    m_pAlignToolBar->addAction(m_pToolsAlignVCenter);
    m_pAlignToolBar->addAction(m_pToolsAlignTop);
    m_pAlignToolBar->addAction(m_pToolsAlignBottom);
    m_pAlignToolBar->addAction(m_pToolsAlignHorizontal);
    m_pAlignToolBar->addAction(m_pToolsAlignVertical);
    m_pAlignToolBar->addAction(m_pToolsAlignHeight);
    m_pAlignToolBar->addAction(m_pToolsAlignWidth);
    m_pAlignToolBar->addAction(m_pToolsAlignWidthAndHeight);
}

DrawView *MainWindow::CreateMdiChild()
{
    DrawScene *scene = new DrawScene();
    QRectF rc = this->rect();
    scene->setSceneRect(rc);
    scene->setBackgroundBrush(Qt::darkGray);

    DrawView *view = new DrawView(scene);
    connect(view,SIGNAL(PositionChanged(const int, const int)),this,SLOT(PositionChanged(const int, const int)));

    // move orign point to leftbottom
    view->setTransform(view->transform().scale(1,-1));

    scene->setView(view);
    m_pMdiArea->addSubWindow(view);

    view->showMaximized();
    return view;
}

void MainWindow::Open()
{
    QMessageBox::information(this, "Open", "Open");
}

void MainWindow::New()
{
    m_pView = CreateMdiChild();
}

void MainWindow::Save()
{
    QMessageBox::information(this, "Save", "Save");
}

void MainWindow::Quit()
{
    this->close();
}

void MainWindow::ZoomIn()
{
    m_pView->zoomIn();
}

void MainWindow::ZoomOut()
{
    m_pView->zoomOut();
}

void MainWindow::PositionChanged(const int x, const int y)
{
    statusBar()->showMessage(QString("%1,%2").arg(x).arg(y));
}

void MainWindow::AddShape()
{
    if ( sender() == m_pToolsShapeSelect )
        DrawTool::c_drawShape = DS_Selection;
    else if (sender() == m_pToolsShapeLine )
        DrawTool::c_drawShape = DS_Line;
    else if ( sender() == m_pToolsShapeRect )
        DrawTool::c_drawShape = DS_Rectangle;
    else if ( sender() == m_pToolsShapeRoundRect )
        DrawTool::c_drawShape = DS_Roundrect;
    else if ( sender() == m_pToolsShapeEllipse )
        DrawTool::c_drawShape = DS_Ellipse ;
    else if ( sender() == m_pToolsShapePolygon )
        DrawTool::c_drawShape = DS_Polygon;
    else if (sender() == m_pToolsShapePolyline )
        DrawTool::c_drawShape = DS_Polyline;
    else if ( sender() == m_pToolsShapeBezier )
        DrawTool::c_drawShape = DS_Bezier ;
    else if (sender() == m_pToolsShapeRotate )
        DrawTool::c_drawShape = DS_Rotation;

    // 非选中和旋转的情况下，清除选中的状态
    if ( sender() != m_pToolsShapeSelect &&
        sender() != m_pToolsShapeRotate )
    {
        m_pView->scene()->clearSelection();
    }
}

