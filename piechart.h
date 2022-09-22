#ifndef PIECHART_H
#define PIECHART_H

#include <basechart.h>
#include <datamodel.h>

class PieChart: public BaseChart
{
    Q_OBJECT

public:
    PieChart(DataModel* model);
    ~PieChart()=default;

    QChart* toChart() override;
    void dataToSeries(QChart* chart) override;
};

#endif // PIECHART_H
