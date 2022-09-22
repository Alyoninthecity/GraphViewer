#ifndef BARCHART_H
#define BARCHART_H

#include <basechart.h>
#include <datamodel.h>

class BarChart : public BaseChart
{
    Q_OBJECT
private:
    QBarCategoryAxis *XAxis;
    QValueAxis *YAxis;
public:
    BarChart(DataModel* model);
    ~BarChart();

    QChart* toChart() override;
    void dataToSeries(QChart* chart) override;
};

#endif // BARCHART_H
