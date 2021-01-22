#ifndef CSTATISTICAL_H
#define CSTATISTICAL_H

#include <QWidget>

namespace Ui {
class CStatistical;
}

class CStatistical : public QWidget
{
    Q_OBJECT

public:
    explicit CStatistical(QWidget *parent = nullptr);
    ~CStatistical();

private:
    Ui::CStatistical *ui;
};

#endif // CSTATISTICAL_H
