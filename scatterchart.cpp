#include "scatterchart.h"

ScatterChart::ScatterChart(DataModel *model): BaseChart(model),XAxis(new QCategoryAxis()), YAxis(new QValueAxis()){}

ScatterChart::~ScatterChart()
{
    delete XAxis;
    delete YAxis;
}

void ScatterChart::dataToSeries(QChart *chart)
{
    std::vector<std::vector<float>> data = model->getData();
    std::vector<QVariant> rowHeader = model->getRowHeader();
    std::vector<QScatterSeries *> scatterSeries;
    for (int i = 0; i < model->rowCount(); i++)
    {
        QScatterSeries *series = new QScatterSeries;
        series->setName(rowHeader[i].toString());

        for (int j = 0; j < model->columnCount(); j++){
            series->append(QPointF(j, data[i].at(j)));
            series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        }

        chart->addSeries(series);
        scatterSeries.push_back(series);

        series->attachAxis(XAxis);
        series->attachAxis(YAxis);
    }
    float min = model->min();
    if (min >= 0)
        YAxis->setRange(0, model->max()*1.3);
    else
        YAxis->setRange(min, model->max()*1.3);
    XAxis->setRange(-0.5, model->columnCount()-0.5);
}

QChart *ScatterChart::toChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Scatter Chart");
    chart->setAnimationOptions(QChart::AllAnimations);
    std::vector<QVariant> colHeader = model->getColHeader();

    for (int i = 0; i < model->columnCount(); i++)
        XAxis->append(colHeader[i].toString(), i);

    XAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addAxis(XAxis, Qt::AlignBottom);
    chart->addAxis(YAxis, Qt::AlignLeft);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ScatterChart::dataToSeries(chart);
    return chart;
}
