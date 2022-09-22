#include "polarchart.h"

PolarChart::PolarChart(DataModel *model): BaseChart(model),XAxis(new QCategoryAxis()), YAxis(new QValueAxis()){}

PolarChart::~PolarChart()
{
    delete XAxis;
    delete YAxis;
}

void PolarChart::dataToSeries(QChart *chart)
{
    std::vector<std::vector<float>> data = model->getData();
    std::vector<QVariant> rowHeader = model->getRowHeader();
    std::vector<QSplineSeries*> splineSeries;

    for (int i = 0; i < model->rowCount(); i++)
    {
        QSplineSeries *series = new QSplineSeries;
        series->setName(rowHeader[i].toString());

        for (int j = 0; j < model->columnCount(); j++)
            series->append(QPointF(j, data[i].at(j)));

        QAreaSeries *serie= new QAreaSeries(series);
        serie->setName(rowHeader[i].toString());
        chart->addSeries(series);
        splineSeries.push_back(series);

        series->attachAxis(XAxis);
        series->attachAxis(YAxis);
    }
    XAxis->setRange(0, model->columnCount());
    YAxis->setRange(model->min(), model->max());
}

QChart *PolarChart::toChart()
{
    std::vector<QVariant> colHeader = model->getColHeader();
    QPolarChart* chart= new QPolarChart();
    chart->setTitle("Polar Chart");
    chart->setAnimationOptions(QChart::AllAnimations);

    for (int i = 0; i < model->columnCount(); i++)
        XAxis->append(colHeader[i].toString(), i);

    XAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addAxis(XAxis, QPolarChart::PolarOrientationAngular);
    chart->addAxis(YAxis, QPolarChart::PolarOrientationRadial);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    PolarChart::dataToSeries(chart);
    return chart;
}
