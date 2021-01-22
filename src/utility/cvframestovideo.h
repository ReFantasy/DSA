/************************************************************************
*
* 文件名：cvframestovideo.h
*
* 文件描述：OpenCV Mats 转为 Video
*
* 创建人：TDL
*
* 时  间：2020/10/05
*
* 版本号：1.0
*
* 修改记录：
*
************************************************************************/
#ifndef CVFRAMESTOVIDEO_H
#define CVFRAMESTOVIDEO_H
#include <QUuid>
#include "opencv2/opencv.hpp"

/**
 * @brief 灰度图像生成视频文件
 * @param mats CV_8UC1灰度图
 * @param sz 视频帧尺寸
 * @param fps 帧率
 * @return 随机产生的视频名称,失败产生空字符串
 */
QString CvFramesToVideo(std::vector<cv::Mat> mats, cv::Size sz, double fps = 25);

#endif // CVFRAMESTOVIDEO_H
