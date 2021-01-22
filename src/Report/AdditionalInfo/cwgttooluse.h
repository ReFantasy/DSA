/************************************************************************
*
* cwgttooluse.h
*
* 文件描述：
*
* 创建人：LYH
*
* 时  间：2020-10-
*
* 版本号 1.0
*
************************************************************************/
#ifndef CWGTTOOLUSE_H
#define CWGTTOOLUSE_H

#include <QWidget>

struct SToolUse
{
    QString sXGMC;
    QString sDSGC;
    QString sDSJK;
    QString sQNGC;
    QString sQNJK;
    QString sDESGC;
    QString sDESJK;
    QString sBMSGC;
    QString sBMSJK;
};

namespace Ui {
class CWgtToolUse;
}

class CWgtToolUse : public QWidget
{
    Q_OBJECT

public:
    explicit CWgtToolUse(QWidget *parent = nullptr);
    ~CWgtToolUse();
    void SetTool(SToolUse pTool);

private:
    Ui::CWgtToolUse *ui;
};

#endif // CWGTTOOLUSE_H
