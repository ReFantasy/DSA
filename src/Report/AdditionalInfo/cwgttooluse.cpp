#include "cwgttooluse.h"
#include "ui_cwgttooluse.h"

CWgtToolUse::CWgtToolUse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWgtToolUse)
{
    ui->setupUi(this);
}

CWgtToolUse::~CWgtToolUse()
{
    delete ui;
}

/**
 * @brief CWgtToolUse::SetTool
 * @param pBXG
 */
void CWgtToolUse::SetTool(SToolUse pTool)
{
    ui->m_grpToolUse->setTitle(pTool.sXGMC);
    ui->m_lineDSGC->setText(pTool.sDSGC);
    ui->m_lineDSJK->setText(pTool.sDSJK);
    ui->m_lineQNGC->setText(pTool.sQNGC);
    ui->m_lineQNJK->setText(pTool.sQNJK);
    ui->m_lineDESGC->setText(pTool.sDESGC);
    ui->m_lineDESJK->setText(pTool.sDESJK);
    ui->m_lineBMSGC->setText(pTool.sBMSGC);
    ui->m_lineBMSJK->setText(pTool.sBMSJK);
}
