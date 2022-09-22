#include "areachart.h"

AreaChart::AreaChart(DataModel *model): BaseChart(model),XAxis(new QCategoryAxis()), YAxis(new QValueAxis()){}

AreaChart::~AreaChart()
{
    delete XAxis;
    delete YAxis;
}

void AreaChart::dataToSeries(QChart *chart)
{
    std::vector<std::vector<float>> data = model->getData();
    std::vector<QVariant> rowHeader = model->getRowHeader();
    std::vector<QLineSeries *> sets;

    for (int i = 0; i < model->rowCount(); i++)
    {
        QLineSeries *series = new QLineSeries;
        series->setName(rowHeader[i].toString());

        for (int j = 0; j < model->columnCount(); j++)
            series->append(QPointF(j, data[i].at(j)));

        QAreaSeries *AreaSerie= new QAreaSeries(series);
        AreaSerie->setName(rowHeader[i].toString());
        chart->addSeries(AreaSerie);

        sets.push_back(series);
        AreaSerie->attachAxis(XAxis);
        AreaSerie->attachAxis(YAxis);
    }

    XAxis->setRange(0, model->columnCount()-1 > 0 ? model->columnCount()-1 : model->columnCount());
    float min = model->min();
    float max = model->max();
    if (min < max)
        YAxis->setRange(model->min(), model->max());
    else
        YAxis->setRange(model->min(), model->min()+1);
}

QChart *AreaChart::toChart()
{
    std::vector<QVariant> colHeader = model->getColHeader();
    QChart *chart = new QChart();
    chart->setTitle("Area Chart");
    chart->setAnimationOptions(QChart::AllAnimations);

    for(int i = 0; i < model->columnCount(); i++)
        XAxis->append(colHeader[i].toString(), i);

    XAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    chart->addAxis(XAxis, Qt::AlignBottom);
    chart->addAxis(YAxis, Qt::AlignLeft);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    AreaChart::dataToSeries(chart);

    return chart;
}
