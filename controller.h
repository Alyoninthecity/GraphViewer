#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <datamodel.h>
#include <graphviewer.h>

#include "barchart.h"
#include "piechart.h"
#include "linechart.h"
#include "areachart.h"
#include "scatterchart.h"
#include "polarchart.h"

#include <QFileDialog>

class Controller : public QObject
{
    Q_OBJECT
private:
    DataModel* model;
    GraphViewer* view;
    QString currentDirectory = "/home";

public:
    explicit Controller(QObject *parent = nullptr);
    void setModel(DataModel* m);
    void setView(GraphViewer* v);
    DataModel* getModel() const;

public slots:
    void newP();
    void graph(int n);
    void bar();
    void pie();
    void line();
    void area();
    void scatter();
    void polar();
    void update();
    void openJson();
    void openS1();
    void openS2();
    void openS3();
    void saveJson() const;
    void editHHeader(int section);
    void editVHeader(int section);
    void addCols();
    void addRows();
    void removeCol();
    void removeRow();
};

#endif // CONTROLLER_H
