#ifndef CWGTANALYSIS_H
#define CWGTANALYSIS_H

#include <QWidget>
#include <qtabbar.h>
#include <qstylepainter.h>
#include <qstyleoption.h>


namespace Ui {
class CWgtAnalysis;
}

class CWgtAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit CWgtAnalysis(QWidget *parent = nullptr);
    ~CWgtAnalysis();

private:
    Ui::CWgtAnalysis *ui;
};

#endif // CWGTANALYSIS_H
