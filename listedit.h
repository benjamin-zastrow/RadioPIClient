#ifndef LISTEDIT_H
#define LISTEDIT_H

#include <QDialog>
#include <QFile>
#include <QStandardItemModel>
#include <QTextStream>
#include <QVector>

namespace Ui {
class ListEdit;
}

class ListEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ListEdit(QWidget *parent = 0);
    ~ListEdit();

private slots:
    void on_addStation_clicked();

    void on_removeStation_clicked();

    void on_finish_clicked();

private:
    Ui::ListEdit *ui;
    QFile *stationlistFile;
    QStandardItemModel *model;
    QVector<QString> *data;
};

#endif // LISTEDIT_H
