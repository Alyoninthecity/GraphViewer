#include "controller.h"
#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent){
    model = new DataModel();
}

void Controller::setModel(DataModel *m){ model=m; }

void Controller::setView(GraphViewer *v){  view=v; }

DataModel* Controller::getModel() const { return model;}

void Controller::newP()
{
    try{
        std::pair<int,int> p= view->showNewProjectDialog();
        model->newDataModel(p.second, p.first);
        view->updateModel();
        view->setChart(new LineChart(getModel()));
        view->showChart();
    }catch(std::runtime_error exc) {
        view->showDialog(exc.what());
    }
}

void Controller::graph(int n)
{
    switch (n) {
        case 0:
        {
            line();
            break;
        }
        case 1:
        {
            bar();
            break;
        }
        case 2:
        {
            pie();
            break;
        }
        case 3:
        {
            area();
            break;
        }
        case 4:
        {
            scatter();
            break;
        }
        case 5:
        {
            polar();
            break;
        }
        default:
        {
            std::cerr<<"error: invalid option";
            view->setChartType(-1);
            break;
        }
    }
}

void Controller::line()
{
    view->setChartType(0);
    view->setChart(new LineChart(getModel()));
    view->showChart();
}

void Controller::bar()
{
    float min = model->min();
    float max = model->max();
    //qInfo()<<"Numero min:" <<min <<" max: "<< max;
    if (min ==0 && max == 0){
        view->showDialog("Your table is empty :( no BarChart for you \n\nTry again by entering some values :)");
    }else {
        view->setChartType(1);
        view->setChart(new BarChart(getModel()));
        view->showChart();
    }
}

void Controller::pie()
{
    view->setChartType(2);
    view->setChart(new PieChart(getModel()));
    view->showChart();
    if(getModel()->columnCount() > 1)
    {
        view->showDialog("Remember: Pie Charts only consider the first column of your dataset.");
    }
}

void Controller::area()
{
    view->setChartType(3);
    view->setChart(new AreaChart(getModel()));
    view->showChart();
}

void Controller::scatter()
{
    view->setChartType(4);
    view->setChart(new ScatterChart(getModel()));
    view->showChart();
}

void Controller::polar()
{
    view->setChartType(5);
    view->setChart(new PolarChart(getModel()));
    view->showChart();
}

void Controller::update()
{
    graph(view->getChartType());
}

void Controller::openJson()
{
    try{
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Open JSON a file"), "", tr("Json file (*.json)"));
    model->readJson(path.toStdString());
    view->updateModel();
    graph(0);
    } catch(std::exception e){
        view->showDialog("Invalid JSON File");
    }
}

void Controller::openS1()
{
    try{
        QString path= ":/samples/petrol.json";
        model->readJson(path.toStdString());
        view->updateModel();
        graph(5);
    }
    catch(std::exception e){
            view->showDialog("Invalid JSON File");
    }
}

void Controller::openS2()
{
    try{
        QString path= ":/samples/inflation.json";
        model->readJson(path.toStdString());
        view->updateModel();
        graph(1);
    }
    catch(std::exception e){
            view->showDialog("Invalid JSON File");
    }
}

void Controller::openS3()
{
    try{
        QString path= ":/samples/population.json";
        model->readJson(path.toStdString());
        view->updateModel();
        graph(0);
    }
    catch(std::exception e){
            view->showDialog("Invalid JSON File");
    }
}


void Controller::saveJson() const
{
    QString path = QFileDialog::getSaveFileName(nullptr, tr("JSON file"), "", tr("Json file (*.json);"));
    model->writeJson(path.toStdString());
}

void Controller::editHHeader(int section){
    try{
        QString label=view->showUpdateHeaderDialog().toLower();
        std::vector<QVariant> colHeader=model->getColHeader();
        for(int i=0; i<model->columnCount(); i++)
        {
            if(label == colHeader[i].toString().toLower())
                throw std::runtime_error("Invalid label: already existing label");
        }
        model->setHeaderData(section, Qt::Horizontal, label);
    }catch (std::runtime_error exc) {
        view->showDialog(exc.what());
    }
}

void Controller::editVHeader(int section){
    try{
        QString label=view->showUpdateHeaderDialog().toLower();
        std::vector<QVariant> rowHeader=model->getRowHeader();
        for(int i=0; i<model->rowCount(); i++)
        {
            if(label == rowHeader[i].toString().toLower() )
                throw std::runtime_error("Invalid label: already existing label");
        }
        model->setHeaderData(section, Qt::Vertical, label);
    }catch (std::runtime_error exc) {
        view->showDialog(exc.what());
    }
}

void Controller::addCols()
{
    try{
        model->insertColumns(view->showAddColsDialog());
        view->updateModel();
        update();
    }
    catch (std::runtime_error exc) {
        view->showDialog(exc.what());
    }
}

void Controller::addRows()
{
    try{
        model->insertRows(view->showAddRowsDialog());
        view->updateModel();
        update();
    }
    catch (std::runtime_error exc) {
        view->showDialog(exc.what());
    }

}

void Controller::removeCol()
{
    try{
        if(model->removeColumn(view->showRemoveColDialog()))
        {
            view->updateModel();
            update();
        }else{
            view->showDialog(QString("Invalid index!!!"));
        }
    } catch(std::runtime_error exc){
        view->showDialog(exc.what());
    }
}

void Controller::removeRow()
{
    try{
        if(model->removeRow(view->showRemoveRowDialog()))
        {
            view->updateModel();
            update();
        }else{
            view->showDialog(QString("Invalid index!!!"));
        }
    } catch(std::runtime_error exc){
        view->showDialog(exc.what());
    }
}
