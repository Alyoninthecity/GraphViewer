#include "piechart.h"

PieChart::PieChart(DataModel *model): BaseChart(model){}

void PieChart::dataToSeries(QChart *chart)
{
    std::vector<std::vector<float>> data = model->getData();
    std::vector<QVariant> rowHeader = model->getRowHeader();

    QPieSeries *series = new QPieSeries();
    for(int i = 0; i < model->rowCount(); i++)
    {
        series->append(new QPieSlice(rowHeader[i].toString(), data[i][0]));
    }

    chart->addSeries(series);
    series->setHoleSize(0);
    QPieSlice *slice = series->slices().at(0);
    slice->setPen(QPen(Qt::black, 2));
}


QChart *PieChart::toChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Pie Chart");
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    PieChart::dataToSeries(chart);
    return chart;
}
