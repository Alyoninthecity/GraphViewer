#ifndef BASECHART_H
#define BASECHART_H

#include "datamodel.h"
#include <QtCharts>

class BaseChart : public QtCharts::QChart{
    Q_OBJECT
protected:
    DataModel* model;

public:
    BaseChart(DataModel* model);
    virtual ~BaseChart() = default;
    virtual QChart* toChart()=0;
    virtual void dataToSeries(QChart* chart)=0;
};

#endif // BASECHART_H
