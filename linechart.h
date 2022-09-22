#ifndef LINECHART_H
#define LINECHART_H

#include <basechart.h>
#include <datamodel.h>

class LineChart: public BaseChart
{
    Q_OBJECT
private:
    QCategoryAxis *XAxis;
    QValueAxis *YAxis;
public:
    LineChart(DataModel* model);
    ~LineChart();

    QChart* toChart() override;
    void dataToSeries(QChart* chart) override;
};

#endif // LINECHART_H
