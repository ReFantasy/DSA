#include "cwidgetlabexamination.h"
#include "ui_cwidgetlabexamination.h"

CWidgetLabExamination::CWidgetLabExamination(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetLabExamination)
{
    ui->setupUi(this);
    ui->widget_xcg->hide();
    ui->widget_ncg->hide();
    ui->widget_xysh->hide();
    ui->widget_xzgn->hide();
    ui->widget_xdt->hide();
}

/**
 * @brief CWidgetLabExamination::~CWidgetLabExamination
 */
CWidgetLabExamination::~CWidgetLabExamination()
{
    delete ui;
}

/**
 * @brief CWidgetLabExamination::on_checkBox_xcg_toggled
 * @param checked
 */
void CWidgetLabExamination::on_checkBox_xcg_toggled(bool checked)
{
    ui->widget_xcg->setVisible(checked);
    if(checked)
        ui->widget_xcg->show();
    else
        ui->widget_xcg->hide();
}


void CWidgetLabExamination::on_checkBox_ncg_toggled(bool checked)
{
    ui->widget_ncg->setVisible(checked);
    if(checked)
        ui->widget_ncg->show();
    else
        ui->widget_ncg->hide();
}

void CWidgetLabExamination::on_checkBox_xysh_toggled(bool checked)
{
    ui->widget_xysh->setVisible(checked);
    if(checked)
        ui->widget_xysh->show();
    else
        ui->widget_xysh->hide();
}

void CWidgetLabExamination::on_checkBox_xzgn_toggled(bool checked)
{
    ui->widget_xzgn->setVisible(checked);
    if(checked)
        ui->widget_xzgn->show();
    else
        ui->widget_xzgn->hide();
}

void CWidgetLabExamination::on_checkBox_xdt_toggled(bool checked)
{
    ui->widget_xdt->setVisible(checked);
    if(checked)
        ui->widget_xdt->show();
    else
        ui->widget_xdt->hide();
}
