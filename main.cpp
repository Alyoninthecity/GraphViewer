#include <QApplication>
#include <QIcon>
#include "datamodel.h"
#include "controller.h"
#include "graphviewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphViewer w;
    Controller c;
    DataModel m;

    w.setWindowTitle("GraphViewer");
    a.setWindowIcon(QIcon(":/images/mainIcon.png"));

    //style sheet
    QFile styleSheetFile(":/Diffnes.qss");
    styleSheetFile.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet= QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    c.setModel(&m);
    c.setView(&w);
    w.setController(&c);
    w.show();
    w.showDialog("Welcome in GraphViewer!\n\n"
                 "Here you can create costumized charts starting from your own dataset.\n\n"
                 "First of all create a new project or open an already existing one."
                 "\nFill the table with your data, costumize the labels"
                 "\nand then choose between the given chart types to display your chart.\n"
                 "\nCheck the documentation in Help->Documentation for more. Have Fun!!!");
    return a.exec();
}
