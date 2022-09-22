#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QVariant>
#include <vector>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <utility>

class DataModel: public QAbstractTableModel{
    Q_OBJECT
public:
    DataModel(QObject *parent = nullptr, int rows = 5, int columns = 4);

    std::vector<std::vector<float>> getData() const;
    std::vector<QVariant> getRowHeader() const;
    std::vector<QVariant> getColHeader() const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    float min();
    float max();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override ;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(unsigned int nRows);
    bool insertColumns(unsigned int nCols);

    bool removeRow(unsigned int rIndex);
    bool removeColumn(unsigned int cIndex);

    void newDataModel(int nRows, int nCols);

    void readJson(std::string path);
    void writeJson(std::string path);

private:
    std::vector<std::vector<float>> tableData;
    std::vector<QVariant> rowHeader;
    std::vector<QVariant> columnHeader;
};

#endif // DATAMODEL_H
