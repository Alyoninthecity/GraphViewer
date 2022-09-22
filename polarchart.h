#ifndef POLARCHART_H
#define POLARCHART_H

#include <basechart.h>
#include <datamodel.h>

#include <QObject>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QSplineSeries>
#include <QCategoryAxis>

class PolarChart: public BaseChart, virtual public QPolarChart
{
private:
    QCategoryAxis *XAxis;
    QValueAxis *YAxis;
public:
    PolarChart(DataModel* model);
    ~PolarChart();

    QChart* toChart() override;
    void dataToSeries(QChart *chart) override;
};

#endif // POLARCHART_H
