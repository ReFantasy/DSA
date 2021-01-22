/*
 * 类名：SingleImageWidget
 * 描述：继承自widget，用于显示单张图像
 * 作者：TDL
 * 时间：2020/08/21
 */

#ifndef SINGLEIMAGEWIDGET_H
#define SINGLEIMAGEWIDGET_H
#include <QWidget>
#include <QPixmap>
#include <QSettings>

namespace Ui {
class SingleImageWidget;
}

class SingleImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleImageWidget(QWidget *parent = nullptr);
    ~SingleImageWidget();

    void SetImage(const QPixmap &pix);
    void SetFileName(QString filename);
    bool IsSelected()const;
    void SetSelected(bool check);

    void mousePressEvent(QMouseEvent *event)override;

private slots:
    void on_checkBox_clicked(bool checked);

private:
    Ui::SingleImageWidget *ui;
    QString _filename;
    QString _ini_config_name;
    QSettings *settings;

};

#endif // SINGLEIMAGEWIDGET_H
