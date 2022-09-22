#include "barchart.h"

void BarChart::dataToSeries(QChart* chart)
{
    std::vector<std::vector<float>> data = model->getData();
    std::vector<QVariant> rowHeader = model->getRowHeader();
    QBarSeries *series= new QBarSeries();
    std::vector<QBarSet *> sets;

    for (int i = 0; i < model->rowCount(); i++)
    {
        QBarSet *set = new QBarSet(rowHeader[i].toString());

        for (int j = 0; j < model->columnCount(); j++)
            set->append(data[i].at(j));
        series->append(set);
        sets.push_back(set);
    }
    chart->addSeries(series);

    chart->addAxis(XAxis, Qt::AlignBottom);
    chart->addAxis(YAxis, Qt::AlignLeft);
    series->attachAxis(XAxis);
    series->attachAxis(YAxis);

}

QChart* BarChart::toChart(){
    std::vector<QVariant> colHeader = model->getColHeader();
    QChart *chart = new QChart();
    chart->setTitle("Bar Chart");
    chart->setAnimationOptions(QChart::AllAnimations);
    for (int i = 0; i < model->columnCount(); i++)
        XAxis->append(colHeader[i].toString());

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    BarChart::dataToSeries(chart);
    return chart;
}

BarChart::BarChart(DataModel *model): BaseChart(model),XAxis(new QBarCategoryAxis()), YAxis(new QValueAxis()){}

BarChart::~BarChart()
{
    delete XAxis;
    delete YAxis;
}
