#include "cwgtanalysis.h"
#include "ui_cwgtanalysis.h"

CWgtAnalysis::CWgtAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWgtAnalysis)
{
    ui->setupUi(this);


}

CWgtAnalysis::~CWgtAnalysis()
{
    delete ui;
}
