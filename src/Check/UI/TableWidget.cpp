#include "TableWidget.h"
#include <QModelIndex>
#include <QDebug>
#include <QMouseEvent>


TableWidget::TableWidget(QWidget *parent)
    :QTableWidget(parent)
{
    //connect(this, &TableWidget::itemSelectionChanged, this, &TableWidget::SelectionChanged);
    _pop_menu = new QMenu(this);
}

void TableWidget::UpdateTable(QTreeWidgetItem *item, int column)
{
    // 如果是病人列表根项发生改变则忽略
    if(item->parent()==nullptr)
        return;

    if(item->checkState(column) == Qt::Unchecked)
    {
        auto data = item->data(1,Qt::UserRole);
        QModelIndex index =  data.value<QModelIndex>();
        auto table_row_index = _model_index_list.indexOf(index);
        // 删除一行
        _model_index_list.removeOne(index);
        removeRow(table_row_index);
    }
    else
    {
        auto data = item->data(1,Qt::UserRole);
        QModelIndex index =  data.value<QModelIndex>();

        // 添加一行
        _model_index_list.push_back(index);
        insertRow(_model_index_list.size()-1);
        UpdateRecord(_model_index_list.size()-1, index);
    }

}

void TableWidget::QueryUpdate(QList<QModelIndex>)
{
    _model_index_list.clear();
    while(rowCount())removeRow(0);
}

void TableWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QTableWidget::mousePressEvent(event);

        int row = currentRow();
        if(row>=0)SendCurrentSelectedModelIndex(_model_index_list[row]);
    }
    else if(event->button()==Qt::RightButton)
    {
        QTableWidget::mousePressEvent(event);
        _pop_menu->exec(QCursor::pos());
    }

}



void TableWidget::UpdateRecord(int row, QModelIndex index)
{
    int cols = index.model()->columnCount();
    for(int i = 0;i<cols;i++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem;
        auto itemindex = index.model()->index(index.row(), i, QModelIndex{});
        newItem->setData(Qt::DisplayRole, index.model()->data(itemindex, Qt::DisplayRole));
        setItem(row, i, newItem);
    }

}
