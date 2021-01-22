#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QList>
#include <QModelIndex>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QMenu>
#include "cwidgetreport.h"

class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = nullptr);

    QMenu *GetMenu()
    {
        return _pop_menu;
    }


public slots:
    void UpdateTable(QTreeWidgetItem *item, int column);

    // 主界面进行了新的查询 病人的表格需要将历史结果删除
    void QueryUpdate(QList<QModelIndex>);

signals:
    void SendCurrentSelectedModelIndex(QModelIndex);

protected:
    void mousePressEvent(QMouseEvent *event)override;



private:
    // 需要显示的数据索引
    QList<QModelIndex> _model_index_list;

    void UpdateRecord(int row, QModelIndex index);

    // 报告模块指针
    CWidgetReport *_widget_report;

    // 弹出菜单
    QMenu *_pop_menu;


};

#endif // TABLEWIDGET_H
