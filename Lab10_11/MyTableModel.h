#pragma once
#include <qabstractitemmodel.h>
#include "Car.h"
#include <vector>
using std::vector;
class MyTableModel :
    public QAbstractTableModel
{
private:
    vector <Car> v;

public:
    MyTableModel(vector<Car>& v) :v{ v } {};
    // number of rows
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    // number of columns
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setCars(vector <Car> cars);
};

