#ifndef AREACHART_H
#define AREACHART_H

#include <basechart.h>
#include <datamodel.h>

class AreaChart: public BaseChart
{
    Q_OBJECT
private:
    QCategoryAxis *XAxis;
    QValueAxis *YAxis;
public:
    AreaChart(DataModel* model);
    ~AreaChart();

    QChart* toChart() override;
    void dataToSeries(QChart* chart) override;
};

#endif // AREACHART_H
