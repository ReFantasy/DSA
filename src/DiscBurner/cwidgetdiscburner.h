#ifndef CWIDGETDISCBURNER_H
#define CWIDGETDISCBURNER_H

#include <QWidget>

namespace Ui {
class CWidgetDiscBurner;
}

class CWidgetDiscBurner : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetDiscBurner(QWidget *parent = nullptr);
    ~CWidgetDiscBurner();


private slots:
    void on_btn_open_door_clicked();

    void on_btn_close_door_clicked();

private:
    Ui::CWidgetDiscBurner *ui;
};

#endif // CWIDGETDISCBURNER_H
