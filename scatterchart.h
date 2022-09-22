#ifndef SCATTERCHART_H
#define SCATTERCHART_H

#include <basechart.h>
#include <datamodel.h>

class ScatterChart: public BaseChart
{
    Q_OBJECT
private:
    QCategoryAxis *XAxis;
    QValueAxis *YAxis;
public:
    ScatterChart(DataModel* model);
    ~ScatterChart();

    QChart* toChart() override;
    void dataToSeries(QChart* chart) override;
};

#endif // SCATTERCHART_H
