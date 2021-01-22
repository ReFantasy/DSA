#include "TreeWidgetWithCheckBox.h"
#include <QTreeWidgetItem>
#include <QDebug>

TreeWidgetWithCheckBox::TreeWidgetWithCheckBox(QWidget *parent)
    :QTreeWidget(parent)
{

    // 隐藏header
    setHeaderHidden(true);

    // 复选框状态改变信号和槽进行连接
    connect(this, &QTreeWidget::itemChanged, this, &TreeWidgetWithCheckBox::UpdateChildItem);
}

void TreeWidgetWithCheckBox::QueryUpdate(QList<QModelIndex> index_list)
{
    // 清空已有病人列表
    clear();
    _index_list = index_list;
    if(_index_list.size()<=0)return;

    // 添加检索结果到影像柜
    QTreeWidgetItem *root_item = new QTreeWidgetItem();
    root_item->setText(0,"影像");
    root_item->setCheckState(0,Qt::Unchecked);  // 影像柜设置为未选中状态

    int rows = _index_list.size();
    for(int i = 0;i<rows;i++)
    {
        // 挂到列表控件上
        auto name = _index_list[i].data(Qt::DisplayRole);

        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0,name.toString());
        item->setCheckState(0,Qt::Unchecked);        // 影像柜设置为未选中状态
        item->setData(1,Qt::UserRole, _index_list[i]);

        root_item->addChild(item);
    }
    addTopLevelItem(root_item);
    expandAll();
}

void TreeWidgetWithCheckBox::UpdateParentItem(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *parent = item;

    if(parent == nullptr)
        return;

    // 选中的子节点数
    int selectedCount = 0;
    // 子节点个数
    int childCount = parent->childCount();

    for(int i = 0;i<childCount;i++)
    {
        auto childItem = parent->child(i);
        if(childItem->checkState(column) == Qt::Checked)
        {
            selectedCount++;
        }
    }

    if(selectedCount <=0)
    {
        // 子节点未选中
        parent->setCheckState(column, Qt::Unchecked);
    }
    else if(selectedCount>0 && selectedCount<childCount)
    {
        // 子节点部分选中
        parent->setCheckState(column, Qt::PartiallyChecked);
    }
    else if(selectedCount == childCount)
    {
        // 子节点全部选中
        parent->setCheckState(column, Qt::Checked);
    }
}



void TreeWidgetWithCheckBox::UpdateChildItem(QTreeWidgetItem *item, int column)
{
    // 获取父项
    QTreeWidgetItem *parent = item->parent();

    // 更新item的子项
    if(item->checkState(column) == Qt::Checked)
    {
        int cnt = item->childCount();
        if(cnt >0)
        {
            for(int i = 0;i<cnt;i++)
            {
                item->child(i)->setCheckState(column, Qt::Checked);
            }
        }
        else
        {
            UpdateParentItem(parent); // 更新父项
        }
    }
    else if(item->checkState(column) == Qt::Unchecked)
    {
        int cnt = item->childCount();
        if(cnt >0 )
        {
            for(int i = 0;i<cnt;i++)
            {
                item->child(i)->setCheckState(column, Qt::Unchecked);
            }
        }
        else
        {
            UpdateParentItem(parent); // 更新父项
        }
    }
}
