#ifndef CSURTYPE_H
#define CSURTYPE_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class CSurType;
}

class CSurType : public QWidget
{
    Q_OBJECT

public:
    explicit CSurType(QWidget *parent = nullptr);
    ~CSurType();

    void SetSurgType(QStringList surg_types);

private slots:
    void UpdateSelected(QListWidgetItem *item);

    void on_clear_selected_clicked();

    void on_pushButton_clicked();

signals:
    void SendSelectedTypes(QStringList _selected_types);

private:
    Ui::CSurType *ui;

    QStringList _surg_types;
    QStringList _selected_types;
};

#endif // CSURTYPE_H
