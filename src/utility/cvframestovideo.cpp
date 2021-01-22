#include "cvframestovideo.h"
//#include "easyloggingpp/easylogging++.h"

QString CvFramesToVideo(std::vector<cv::Mat> mats, cv::Size sz, double fps)
{
    auto _video_name = QUuid::createUuid().toString()+".avi";

    //创建 writer，并指定 FOURCC 及 FPS 等参数
    cv::VideoWriter writer = cv::VideoWriter(_video_name.toStdString(),CV_FOURCC('M','J','P','G'), fps, sz, false);
    //检查是否成功创建
    if(!writer.isOpened())
    {
        //LOG(ERROR)<< "Can not create video file.\n";
        return QString();
    }

    cv::Mat tmp;
    for(auto mat:mats )
    {
        cv::resize(mat, tmp, sz);
        //将图像写入视频
        writer << tmp;
    }

    return _video_name;
}
