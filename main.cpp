#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

//    QtRuleBar rule(Qt::Orientation::Vertical);
//    rule.show();

    return a.exec();
}
