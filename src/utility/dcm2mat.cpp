#include "dcm2mat.h"
#include <QDebug>
#include <iostream>
#include <QPixmap>
#include "dcmtk/dcmdata/dcfilefo.h"
//#include "dcmtk/dcmdata/dcdatset.h"
#include "dcmtk/dcmimgle/dcmimage.h"
//#include "dcmtk/dcmdata/dctagkey.h"
//#include "dcmtk/ofstd/ofstring.h"
//#include "dcmtk/ofstd/ofcond.h"
//#include "dcmtk/dcmjpeg/djdecode.h"
#include <opencv2/opencv.hpp>

#define IMAGE_SIZE 128


bool Dcm2QPixmaps(const char* fileName, std::vector<QPixmap> &pixmaps)
{
    // 载入DICOM影像
    DcmFileFormat dff;
    OFCondition oc = dff.loadFile(fileName);
    if (!oc.good()){
        return false;
    }
    DcmDataset *dataset = dff.getDataset();
    DicomImage *dcm_img = new DicomImage(dataset,dataset->getOriginalXfer());

    // 获取dcm文件信息
    int dcm_frames = dcm_img->getNumberOfFrames();
    if (dcm_frames <= 0)
    {
        delete dcm_img;
        return false;
    }

    int width = dcm_img->getWidth();
    int height = dcm_img->getHeight();

    // 由dcm数据生成Qt可显示图像格式
    // 依次读取每一帧数据
    pixmaps = std::vector<QPixmap>(dcm_frames, QPixmap{});
    for (int i = 0; i < dcm_frames; i++)
    {
        unsigned char *pixelData = (unsigned char*)(dcm_img->getOutputData(8, i, 0));	//获得16位的图像数据指针
        QImage image(pixelData, width, height, width, QImage::Format_Indexed8);
        auto pix= QPixmap::fromImage(image);
        pix = pix.scaled({IMAGE_SIZE,IMAGE_SIZE});
        pixmaps[i] = pix;
    }
    delete dcm_img;

    return true;
}

bool Dcm2QPixmap(const char* fileName, QPixmap &pix)
{
    // 载入DICOM影像
    DcmFileFormat dff;
    OFCondition oc = dff.loadFile(fileName);
    if (!oc.good()){
        return false;
    }
    DcmDataset *dataset = dff.getDataset();
    DicomImage *dcm_img = new DicomImage(dataset,dataset->getOriginalXfer());

    // 获取dcm文件信息
    int dcm_frames = dcm_img->getNumberOfFrames();
    if (dcm_frames <= 0)
    {
        delete dcm_img;
        return false;
    }

    int width = dcm_img->getWidth();
    int height = dcm_img->getHeight();

    // 由dcm数据生成Qt可显示图像格式
    unsigned char *pixelData = (unsigned char*)(dcm_img->getOutputData(8, 0, 0));	//获得16位的图像数据指针
    QImage image(pixelData, width, height, width, QImage::Format_Indexed8);
    pix = QPixmap::fromImage(image);
    pix = pix.scaled({IMAGE_SIZE,IMAGE_SIZE});
    delete dcm_img;

    return true;
}

