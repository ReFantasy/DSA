#include "acquiredcmfile.h"
#include <QDir>
#include <QString>
#include <thread>
#include "dcm2mat.h"
#include "dsaconfig.h"
#include "easyloggingpp/easylogging++.h"
#include <QDebug>
#include <QProgressDialog>
#include <QApplication>
#include "SQLDB.h"

std::vector<std::vector<QPixmap>> AcquireDcmFile(std::string patient_id, QStringList &file_names)
{
    auto _patient_id = patient_id;

    // 从共享文件夹读取图像
    //qDebug()<<DsaConfig::GetDB()[0];
    auto filder = DsaConfig::GetSharedDcmFolder();
    auto _paht = QString("\\\\%1\\%2\\%3").arg(DsaConfig::GetDB()[0], filder, QString(_patient_id.c_str()));

    auto path = DsaConfig::GetSharedDcmFolder().toStdString() + _patient_id;
    QDir dir = QString(_paht);

    if(!dir.exists())
    {
        LOG(ERROR)<<QString("path : %1 is not exist.").arg(dir.path());
        return {};
    }
    QStringList file_list = dir.entryList(QDir::Files);
    const int image_number = file_list.size();

    std::vector<std::vector<QPixmap>> vec_pixs(image_number, std::vector<QPixmap>{});

    // 添加一个进度条
    QProgressDialog process;
    process.setWindowTitle("Reading Image From Server");
    process.setLabelText(QObject::tr("正在读取影像"));
    process.setRange(0,vec_pixs.size());
    process.setWindowFlag(Qt::FramelessWindowHint);
    process.setCancelButton(nullptr);
    process.setStyleSheet("QProgressDialog {border: 2px solid grey;border-radius: 5px;}"
                          "QProgressBar {border: 2px solid grey;border-radius: 5px;}"
                          "QProgressBar::chunk {background-color: #05B8CC;width: 20px;}"
                          "QProgressBar {border: 2px solid grey;border-radius: 5px;text-align: center;}");
    process.setModal(true);
    process.show();

    for(int i = 0;i<image_number;i++)
    {
        QString abs_filename = dir.absoluteFilePath(file_list[i]);
        file_names.push_back(abs_filename);
        std::vector<QPixmap> pixs;
        if(Dcm2QPixmaps(abs_filename.toStdString().c_str(), pixs))
        {
            vec_pixs[i] = pixs;
        }

        process.setValue(i+1);
        QApplication::processEvents();
    }

    process.setValue(vec_pixs.size());
    process.hide();

    return vec_pixs;
}

