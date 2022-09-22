#include "datamodel.h"
#include <iostream>
#include <QtDebug>

DataModel::DataModel(QObject *parent, int rows, int columns) : QAbstractTableModel(parent)
{
    Q_UNUSED(parent);
    tableData.resize(rows);
    for (int i = 0; i < rows; i++)
        tableData[i].resize(columns);
    rowHeader.resize(rows);
    for (int i = 0; i < rows; i++){
        rowHeader[i]= QVariant(i);
    }
    columnHeader.resize(columns);
    for (int i = 0; i < columns; i++){
        columnHeader[i]=QVariant(i);
    }
}

std::vector<std::vector<float>> DataModel::getData() const
{
    return tableData;
}

std::vector<QVariant> DataModel::getRowHeader() const
{
    return rowHeader;
}

std::vector<QVariant> DataModel::getColHeader() const
{
    return columnHeader;
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return rowHeader.size();
}
int DataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return columnHeader.size();
}


QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()){
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return tableData[index.row()][index.column()];
        }
    }
    return QVariant();
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid()){
        if(role == Qt::EditRole)
        {
            tableData[index.row()].at(index.column()) = value.toFloat();
            emit(dataChanged(index, index));
            return true;
        }
    }
    return false;
}

float DataModel::min()
{
    float m = std::numeric_limits<double>::max();
    for(const auto& row : tableData)
    {
      float minElemInRow = *std::min_element(row.begin(), row.end());
      m = std::min(m , minElemInRow);
    }
    return m;
}

float DataModel::max()
{
    float m= std::numeric_limits<double>::min();
    for(const auto& row : tableData)
    {
      float maxElem = *std::max_element(row.begin(), row.end());
      m = std::max(m , maxElem);
    }
    return m;
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && section >= 0){
        if (orientation == Qt::Vertical)
            return rowHeader[section];
        else
            return columnHeader[section];
    }
    return QVariant();
}

bool DataModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role == Qt::EditRole && section >= 0)
        {
            if (orientation == Qt::Vertical)
                rowHeader[section] = value;
            else
                columnHeader[section]= value;
            emit headerDataChanged(orientation, section, section);
            return true;
        }
        return false;
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool DataModel::insertRows(unsigned int nRows)
{
    beginInsertRows(QModelIndex(), tableData.size(),tableData.size()+nRows-1);
    for(unsigned int i=0; i<nRows; i++)
    {
        rowHeader.push_back(QVariant::fromValue(tableData.size()));
        tableData.push_back(std::vector<float>(columnHeader.size(),0));
        //qInfo()<<"Rows :" <<tableData.size();
    }
    endInsertRows();
    return true;
}

bool DataModel::insertColumns(unsigned int nCols)
{
    beginInsertColumns(QModelIndex(), tableData.size(),tableData.size()+nCols-1);
    for (unsigned int i = 0; i < tableData.size(); i++){
        tableData[i].resize(tableData[i].size()+nCols);
    }
    for (int i = nCols; i > 0; i--)
        columnHeader.push_back(QVariant::fromValue(tableData[0].size()-i));
    endInsertColumns();
    return true;
}

bool DataModel::removeRow(unsigned int rIndex)
{
    if (tableData.size()<=rIndex || tableData.size()<2)
    {
        std::cerr<<"invalid index \n";
        return false;
    }
    //qInfo()<<"Numero Righe Prima:" <<tableData.size();

    tableData.erase(tableData.begin()+rIndex);
    rowHeader.erase(rowHeader.begin()+rIndex);
    //qInfo()<<"Numero Righe Dopo:" <<tableData.size();
    return true;
}

bool DataModel::removeColumn(unsigned int cIndex)
{
    if (tableData[0].size()<=cIndex || tableData[0].size()<2|| tableData.size()<1)
    {
       std::cerr<<"invalid index \n";
       return false;
    }

    std::for_each(tableData.begin(), tableData.end(),[&](std::vector<float>& row) {
        row.erase(std::next(row.begin(), cIndex));
    });
    //qInfo()<<"Numero Colonne:" <<tableData[0].size();

    columnHeader.erase(columnHeader.begin()+cIndex);
    return true;
}

void DataModel::newDataModel(int nRows, int nCols)
{
    rowHeader.clear();
    columnHeader.clear();
    for (unsigned int i = 0; i < tableData.size(); i++){
        tableData[i].clear();
    }
    tableData.clear();

    tableData.resize(nRows);
    for (int i = 0; i < nRows; i++){
        tableData[i].resize(nCols);
    }
    rowHeader.resize(nRows);
    for (int i = 0; i < nRows; i++){
        rowHeader[i]= QVariant(i);
    }
    columnHeader.resize(nCols);
    for (int i = 0; i < nCols; i++){
        columnHeader[i]= QVariant(i);
    }
}

void DataModel::readJson(std::string path)
{
    if(!QString::fromStdString(path).endsWith(".json")){
        throw std::exception();
    }
    QFile file(QString::fromStdString(path));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject object = jsonDocument.object();
    QJsonArray tData = object.value("tableData").toArray();
    QJsonArray rH = object.value("rowHeader").toArray();
    QJsonArray cH = object.value("columnHeader").toArray();

    if(rH.size() == 0 || tData.size() == 0 || cH.size() == 0 ||rH.size() != tData.size()){
        throw std::exception();
    }
    for(int i = 0; i<tData.size();i++){
        if(tData[i].toArray().size() !=cH.size())
            throw std::exception();
    }

    newDataModel(rH.size(),cH.size());

    for (int i = 0; i < rH.size(); i++){
        if(rH[i].isDouble())
            rowHeader[i] = QVariant(rH[i].toDouble());
        else{
            rowHeader[i] = QVariant(rH[i].toString().toLower());
        }
        //qInfo()<< rowHeader[i];
    }
    for (int i = 0; i < cH.size(); i++){
        if(cH[i].isDouble())
            columnHeader[i] = QVariant(cH[i].toDouble());
        else{
            columnHeader[i] = QVariant(cH[i].toString().toLower());
        }
    }
    for (int i = 0; i < tData.size(); i++)
    {
        for (int ii = 0; ii < tData[i].toArray().size(); ii++)
            tableData[i][ii]=tData[i].toArray()[ii].toDouble();
    }
    /*for(auto x : tableData){
        qInfo() << x;
    }*/
}

void DataModel::writeJson(std::string path){
    if(!QString::fromStdString(path).endsWith(".json")){
        path+=".json";
    }
    QFile file(QString::fromStdString(path));
    file.resize(0);
    QJsonObject object;
    QJsonArray rH;
    QJsonArray cH;
    QJsonArray tData;

    for (unsigned int i = 0; i < rowHeader.size(); i++){
        rH.push_back(QJsonValue::fromVariant(rowHeader[i]));
    }
    for (unsigned int i = 0; i < columnHeader.size(); i++){
        cH.push_back(QJsonValue::fromVariant(columnHeader[i]));
    }
    for (unsigned int i = 0; i < tableData.size(); i++)
    {
        QJsonArray temp;
        for (unsigned int ii = 0; ii < tableData[i].size(); ii++)
        {
            //qInfo()<<tableData[i][ii];
            temp.push_back(tableData[i][ii]);
        }
        //qInfo()<<temp<<temp.size();
        tData.push_back(temp);
    }

    object.insert("tableData", tData);
    object.insert("rowHeader", rH);
    object.insert("columnHeader", cH);
    file.open(QIODevice::ReadWrite);
    file.write(QJsonDocument(object).toJson());
    file.close();
}
