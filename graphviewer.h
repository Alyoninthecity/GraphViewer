#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QComboBox>
#include <QtCharts>
#include <QChart>
#include <QChartView>
#include <QTableView>
#include <QIcon>

#include <utility>
#include "datamodel.h"
#include "basechart.h"
#include "doc.h"
#include "aboutus.h"

class Controller;

class GraphViewer : public QWidget {
    Q_OBJECT
public:
    explicit GraphViewer(QWidget *parent = nullptr);

private:

    QGridLayout* mainLayout;
    QTableView* table;
    Controller* controller;
    QChartView *chartView;
    BaseChart *chart;
    int chartType;

    QMenu* file;
    QMenu* options;
    QMenu* graphview;
    QMenu* help;

    QMenu* open;
    QMenu* sample;
    QMenu* save;

    QPushButton* newProjectButton;
    QPushButton* loadButton;
    QPushButton* saveButton;
    QPushButton* addColumnsButton;
    QPushButton* addRowsButton;
    QPushButton* delColumnButton;
    QPushButton* delRowButton;
    QComboBox* chartsButton;
    QPushButton* updateButton;

    void addMenus();
    void addTableScreen();
    void addChartView();
    void addButtons();

public:
    void setController(Controller* c);
    void setHome();
    void updateModel();
    void showDialog(const QString& message);

    QWidget *getChartView() const;
    QWidget *getTableView() const;
    BaseChart *getChart() const;
    void setChart(BaseChart* c);

    int getChartType()const;
    void setChartType(int n);

    std::pair<int,int> showNewProjectDialog();
    unsigned int showRemoveColDialog();
    unsigned int showRemoveRowDialog();
    QString showUpdateHeaderDialog();
    unsigned int showAddColsDialog();
    unsigned int showAddRowsDialog();

    void showChart();
public slots:
    void documentation() const;
    void about() const;
};

#endif // GRAPHVIEWER_H

