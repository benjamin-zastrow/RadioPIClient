#include "listedit.h"
#include "ui_listedit.h"
#include <QMessageBox>
#include <iostream>


ListEdit::ListEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListEdit)
{
    ui->setupUi(this);
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
    model = new QStandardItemModel(0, 2);
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "URL");
    for(int i = 0; !(i == data->length()); ++i)
    {
        QList<QStandardItem*> *list = new QList<QStandardItem*>;
        QStandardItem *itemName, *itemURL;
        itemName = new QStandardItem(data->at(i).split(";").at(0));
        itemURL = new QStandardItem(data->at(i).split(";").at(1));
        list->push_back(itemName);
        list->push_back(itemURL);
        model->appendRow(*list);
    }

    ui->stationTableView->setModel(model);
    ui->stationTableView->setCornerButtonEnabled(false);
    ui->stationTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ListEdit::~ListEdit()
{
    delete ui;
}

void ListEdit::on_addStation_clicked()
{
    if(ui->stationURL->text().isEmpty() || ui->stationTitle->text().isEmpty())
    {
        QMessageBox::warning(this, "Eingabefehler", "Eine Eingabe wurde nicht gemacht", QMessageBox::Ok);
    }
    else
    {
        QList<QStandardItem*> *list = new QList<QStandardItem*>;
        QStandardItem *itemName, *itemURL;
        itemName = new QStandardItem(ui->stationTitle->text());
        itemURL = new QStandardItem(ui->stationURL->text());
        list->push_back(itemName);
        list->push_back(itemURL);
        model->appendRow(*list);
        ui->stationTitle->setText("");
        ui->stationTitle->setFocus();
        ui->stationURL->setText("");
    }
}

void ListEdit::on_removeStation_clicked()
{
    if(ui->stationTableView->selectionModel()->selectedRows().isEmpty())
        return;
    model->removeRow(ui->stationTableView->selectionModel()->selectedRows().first().row());
}

void ListEdit::on_finish_clicked()
{
    if(ui->stationTableView->model()->hasChildren() == false)
        close();
    if(stationlistFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        stationlistFile->flush();
        QTextStream out(stationlistFile);
        for(int i = 0; !(i == ui->stationTableView->model()->rowCount()); ++i)
        {
            out << ui->stationTableView->model()->data(ui->stationTableView->model()->index(i, 0)).toString() << ";" << ui->stationTableView->model()->data(ui->stationTableView->model()->index(i, 1)).toString() << "\n";
        }
        stationlistFile->close();
        close();

    }

}
