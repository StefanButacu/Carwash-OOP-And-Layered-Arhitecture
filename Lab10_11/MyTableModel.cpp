#include "MyTableModel.h"

int MyTableModel::rowCount(const QModelIndex& parent) const
{
    return v.size();
}

int MyTableModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        int poz = index.row();
        Car c = v.at(poz);
        qDebug() << "Row:" << index.row() << " Col:" << index.column();
        if (index.column() == 0)
            return QString::number(c.getNrInmatr());
        if (index.column() == 1)
            // producator 
            return QString::fromStdString(c.getProd());
        if(index.column() == 2)
            // producator 
            return QString::fromStdString(c.getModel());
        if(index.column() == 3)
            return QString::fromStdString(c.getTip());
        }
    return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section == 0)
                return QString::fromStdString("Nr. Inmatric");
            if (section == 1)
                // producator 
                return QString::fromStdString("Producator");
            if (section == 2)
                // model
                return QString::fromStdString("Model");
            if (section == 3)
                return QString::fromStdString("Tip");
        }
        else
            return QString("%1").arg(section);
    }


    return QVariant();
}

void MyTableModel::setCars(vector<Car> cars)
{
    this->v = cars;
    
    emit layoutChanged();
}
