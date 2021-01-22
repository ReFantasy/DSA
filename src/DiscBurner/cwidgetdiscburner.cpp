#include "cwidgetdiscburner.h"
#include "ui_cwidgetdiscburner.h"

#include"windows.h"
#include"mmsystem.h"

#pragma comment(lib, "winmm.lib")

CWidgetDiscBurner::CWidgetDiscBurner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetDiscBurner)
{
    ui->setupUi(this);
}

CWidgetDiscBurner::~CWidgetDiscBurner()
{
    delete ui;
}



void CWidgetDiscBurner::on_btn_open_door_clicked()
{
     mciSendStringA("set cdaudio door open", 0, 0, 0);
}

void CWidgetDiscBurner::on_btn_close_door_clicked()
{
    mciSendStringA( "set cdaudio door closed ", 0, 0, 0);
}
