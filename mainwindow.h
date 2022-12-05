#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#include "netclient.h"
#include "listedit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_volume_valueChanged(int value);
    void onListeBearbeitenClicked();
    void on_volume_sliderReleased();

    void on_SenderList_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    netClient *client;
    ListEdit *le;
    QVector<QString> *data;
    QFile *stationlistFile;
};

#endif // MAINWINDOW_H
