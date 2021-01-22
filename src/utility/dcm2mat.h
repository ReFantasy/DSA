#ifndef DCM2MAT_H
#define DCM2MAT_H
#include <vector>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QList>

/**
 * @brief 多帧Dcm图像生成QPixmap
 * @param fileName Dcm文件名
 * @param pixmaps 生成的QPixmap数组
 * @return 成功返回true,否则返回false
 */
bool Dcm2QPixmaps(const char* fileName, std::vector<QPixmap> &pixmaps);

/**
 * @brief Dcm图像生成QPixmap,多帧返回第一帧
 * @param fileName Dcm文件名
 * @param pix 生成的QPixmap
 * @return 成功返回true,否则返回false
 */
bool Dcm2QPixmap(const char* fileName, QPixmap &pix);


#endif // DCM2MAT_H
