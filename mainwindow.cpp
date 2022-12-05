#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionListe_bearbeiten, SIGNAL(triggered()), this, SLOT(onListeBearbeitenClicked()));
    client = new netClient(this, QInputDialog::getText(this, "IP-Adresse", "Geben sie die IP-Adresse des Servers ein: ", QLineEdit::Normal, "127.0.0.1"));
    data = new QVector<QString>;

    stationlistFile = new QFile("staionlist.dat");
    if(stationlistFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream StationFileStream(stationlistFile);
        while(!StationFileStream.atEnd())
        {
            data->push_back(StationFileStream.readLine());
        }
    }
    stationlistFile->close();

    for(int i = 0; !(i == data->length()); ++i)
    {
        ui->SenderList->addItem(data->at(i).split(";").at(0));
    }
    ui->statusBar->showMessage("Broadcast bereit", 2000);
}

MainWindow::~MainWindow()
{
    QByteArray req = "stop";
    client->writeDatagram(req);
    delete ui;
}

void MainWindow::on_volume_valueChanged(int value)
{
    ui->volPerc->setText(QString("Lautstärke: %1%").arg(value));
}


void MainWindow::on_volume_sliderReleased()
{
    QByteArray req = "vol;" + QByteArray::number(ui->volume->value());
    client->writeDatagram(req);
}
void MainWindow::onListeBearbeitenClicked()
{
    le = new ListEdit;
    le->show();
}

void MainWindow::on_SenderList_currentIndexChanged(int index)
{
    QByteArray req = "play;" + QByteArray(data->at(index).split(";").at(1).toLatin1());
    client->writeDatagram(req);
}
