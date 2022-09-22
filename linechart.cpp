#include "linechart.h"

LineChart::LineChart(DataModel *model): BaseChart(model), XAxis(new QCategoryAxis()), YAxis(new QValueAxis()){}

LineChart::~LineChart()
{
    delete XAxis;
    delete YAxis;
}

void LineChart::dataToSeries(QChart *chart)
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

        chart->addSeries(series);
        sets.push_back(series);
        series->attachAxis(XAxis);
        series->attachAxis(YAxis);
    }

    XAxis->setRange(0, model->columnCount()-1 > 0 ? model->columnCount()-1 : model->columnCount());
    float min = model->min();
    float max = model->max();
    if (min < max)
        YAxis->setRange(model->min(), model->max());
    else
        YAxis->setRange(model->min(), model->min()+1);
}

QChart *LineChart::toChart()
{
    std::vector<QVariant> colHeader = model->getColHeader();
    QChart *chart = new QChart();
    chart->setTitle("Line Chart");
    chart->setAnimationOptions(QChart::AllAnimations);

    for(int i = 0; i < model->columnCount(); i++)
        XAxis->append(colHeader[i].toString(), i);

    XAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addAxis(XAxis, Qt::AlignBottom);
    chart->addAxis(YAxis, Qt::AlignLeft);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
     LineChart::dataToSeries(chart);
    return chart;
}

