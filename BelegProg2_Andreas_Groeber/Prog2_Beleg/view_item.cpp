/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#include "view_item.h"
#include "ui_view_item.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>

#include "buch.h"
#include "cd.h"
#include "item.h"


view_item::view_item(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::view_item)
{
    ui->setupUi(this);

    ui->ItemView->setColumnCount(5);
    ui->ItemView->setRowCount(1);
    ui->ItemView->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
    ui->ItemView->setHorizontalHeaderItem(1,new QTableWidgetItem("Autor"));
    ui->ItemView->setHorizontalHeaderItem(2,new QTableWidgetItem("Art"));
    ui->ItemView->setHorizontalHeaderItem(3,new QTableWidgetItem("Anzahl"));
    ui->ItemView->setHorizontalHeaderItem(4,new QTableWidgetItem("Verfügbar"));




    QFile IFile("Itemlisttest.csv");
    if(!IFile.open(QFile::ReadOnly| QFile::Text))
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("Lesen von itemlist nicht möglich");
        ErrorMsg.exec();
        // return;
    }

    int i=0; //index
    QString item;
    QTextStream in(&IFile);
    while (!in.atEnd())
    {
        item = in.readLine();
        ui->ItemView->insertRow(i);
        QStringList Itemlist  = item.split(QLatin1Char(','));
        ui->ItemView->setItem(i,0,new QTableWidgetItem(Itemlist[0]));
        ui->ItemView->setItem(i,1,new QTableWidgetItem(Itemlist[1]));
        ui->ItemView->setItem(i,2,new QTableWidgetItem(Itemlist[2]));
        ui->ItemView->setItem(i,3,new QTableWidgetItem(Itemlist[3]));
        ui->ItemView->setItem(i,4,new QTableWidgetItem(Itemlist[4]));
        i++;
    }
    IFile.flush();
    IFile.close();



}



view_item::~view_item()
{
    delete ui;
}



void view_item::on_bt_Sort_clicked()                    //sortierfunktion
{
    QFile IFile("Itemlisttest.csv");
    if(!IFile.open(QFile::ReadOnly| QFile::Text))
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("Lesen von itemlist nicht möglich");
        ErrorMsg.exec();
        // return;
    }
    int i=0;
    QString tmp;
    item items[1000];    //1000 Einträge max
    QTextStream in(&IFile);
    while(!in.atEnd())
    {
        tmp = in.readLine();
        QStringList Itemsplit = tmp.split(QLatin1Char(','));
        items[i].Name=      Itemsplit[0];
        items[i].Autor=     Itemsplit[1];
        items[i].Art=       Itemsplit[2];
        items[i].Anzahl=    Itemsplit[3];
        items[i].Verfuegbar=Itemsplit[4];
        i++;
    }
    IFile.close();
    for(int j=0;j<i;j++)
    {
        for(int k=0;k<j;k++)
        {
            item tausch;
            QString str1=items[j].Name;
            QString str2=items[k].Name;
            int x= QString::compare(str1,str2);

            if(x<0)
            {
                tausch = items[j];
                items[j]=items[k];
                items[k]= tausch;
            }
        }
    }
    int l=0;
    while(l<i)
    {
    ui->ItemView->removeRow(l);
    ui->ItemView->insertRow(l);
    ui->ItemView->setItem(l,0,new QTableWidgetItem(items[l].Name));
    ui->ItemView->setItem(l,1,new QTableWidgetItem(items[l].Autor));
    ui->ItemView->setItem(l,2,new QTableWidgetItem(items[l].Art));
    ui->ItemView->setItem(l,3,new QTableWidgetItem(items[l].Anzahl));
    ui->ItemView->setItem(l,4,new QTableWidgetItem(items[l].Verfuegbar));
    l++;
    }

}

void view_item::on_bt_Sort2_clicked()
{
    QFile IFile("Itemlisttest.csv");
    if(!IFile.open(QFile::ReadOnly| QFile::Text))
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("Lesen von itemlist nicht möglich");
        ErrorMsg.exec();
        // return;
    }
    int i=0;
    QString tmp;
    item items[1000];    //1000 Einträge max
    QTextStream in(&IFile);
    while(!in.atEnd())
    {
        tmp = in.readLine();
        QStringList Itemsplit = tmp.split(QLatin1Char(','));
        items[i].Name=      Itemsplit[0];
        items[i].Autor=     Itemsplit[1];
        items[i].Art=       Itemsplit[2];
        items[i].Anzahl=    Itemsplit[3];
        items[i].Verfuegbar=Itemsplit[4];
        i++;
    }
    IFile.close();
    for(int j=0;j<i;j++)                    //kann man noch modifizieren das hier auch noch alphabetisch sortiert wird
    {
        for(int k=0;k<j;k++)
        {
            item tausch;
            QString str1=items[j].Art;
            QString str2=items[k].Art;
            int x= QString::compare(str1,str2);


            if(x<0)
            {
                tausch = items[j];
                items[j]=items[k];
                items[k]= tausch;
            }
        }
    }
    int l=0;
    while(l<i)
    {
    ui->ItemView->removeRow(l);
    ui->ItemView->insertRow(l);
    ui->ItemView->setItem(l,0,new QTableWidgetItem(items[l].Name));
    ui->ItemView->setItem(l,1,new QTableWidgetItem(items[l].Autor));
    ui->ItemView->setItem(l,2,new QTableWidgetItem(items[l].Art));
    ui->ItemView->setItem(l,3,new QTableWidgetItem(items[l].Anzahl));
    ui->ItemView->setItem(l,4,new QTableWidgetItem(items[l].Verfuegbar));
    l++;
    }

}

