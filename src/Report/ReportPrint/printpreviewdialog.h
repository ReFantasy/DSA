#ifndef PRINTPREVIEWDIALOG_H
#define PRINTPREVIEWDIALOG_H
#include <QPrinter>
#include <QPrintPreviewDialog>
#include "isubreport.h"

class PrintPreviewDialog : public QPrintPreviewDialog,public ISubReport
{
    Q_OBJECT

public:
    PrintPreviewDialog(QWidget *parent = nullptr);
    ~PrintPreviewDialog();
	
	/**
     * @brief 设置病例ID
     */
    virtual void SetSysCaseId(const QString)override;

    /**
     * @brief 从数据库请求数据更新界面信息
     */
    virtual void UpdateUIFromDatabase()override{};

    /**
     * @brief 将界面修改信息写回数据库
     */
    virtual void UpdateDatabaseFromUI()override{};

private:
    /**
     * @brief 根据病历号生成报告
     * @param sys_case_id 病历号
     * @return
     */
    QString GenerateHtml(const QString sys_case_id);


public slots:
    void printPreview(QPrinter *printer);

private:
    QString specified;


};
#endif // PRINTPREVIEWDIALOG_H
