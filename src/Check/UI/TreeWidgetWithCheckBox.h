/*
 * 影像柜列表控件
 */
#ifndef TREEWIDGETWITHCHECKBOX_H
#define TREEWIDGETWITHCHECKBOX_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "cquery.h"

class TreeWidgetWithCheckBox : public QTreeWidget
{
    Q_OBJECT

public:
    TreeWidgetWithCheckBox(QWidget *parent = nullptr);

private:
    QList<QModelIndex> _index_list;

public slots:
    // 接收来自主控界面的查询更新信号
    void QueryUpdate(QList<QModelIndex> index_list);

private slots:
    // 更新父子节点复选框
    void UpdateChildItem(QTreeWidgetItem *item, int column = 0);

    void UpdateParentItem(QTreeWidgetItem *item, int column = 0);
};

#endif // TREEWIDGETWITHCHECKBOX_H
