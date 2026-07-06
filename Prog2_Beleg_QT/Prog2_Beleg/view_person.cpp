/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#include "view_person.h"
#include "ui_view_person.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "person.h"

//copy paste von view_item angepasst an Person-Klasse

view_person::view_person(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::view_person)
{
    ui->setupUi(this);

    ui->PersonView->setColumnCount(5);
    ui->PersonView->setRowCount(1);
    ui->PersonView->setHorizontalHeaderItem(0,new QTableWidgetItem("KundenName"));
    ui->PersonView->setHorizontalHeaderItem(1,new QTableWidgetItem("MedienName"));
    ui->PersonView->setHorizontalHeaderItem(2,new QTableWidgetItem("MedienArt"));
    ui->PersonView->setHorizontalHeaderItem(3,new QTableWidgetItem("Adresse"));
    ui->PersonView->setHorizontalHeaderItem(4,new QTableWidgetItem("Rückgabe-Datum"));
    QFile PFile("Personlisttest.csv");
    if(!PFile.open(QFile::ReadOnly| QFile::Text))
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("Lesen von Personlist nicht möglich");
        ErrorMsg.exec();
        // return;
    }

    int i=0; //index
    QString item;
    QTextStream in(&PFile);
    while (!in.atEnd())
    {
        item = in.readLine();
        ui->PersonView->insertRow(i);
        QStringList Itemlist  = item.split(QLatin1Char(','));
        ui->PersonView->insertRow(i);
        ui->PersonView->setItem(i,0,new QTableWidgetItem(Itemlist[0]));
        ui->PersonView->setItem(i,1,new QTableWidgetItem(Itemlist[1]));
        ui->PersonView->setItem(i,2,new QTableWidgetItem(Itemlist[2]));
        ui->PersonView->setItem(i,3,new QTableWidgetItem(Itemlist[3]));
        ui->PersonView->setItem(i,4,new QTableWidgetItem(Itemlist[4]));
        i++;
    }
    PFile.flush();
    PFile.close();




}


view_person::~view_person()
{
    delete ui;
}

void view_person::on_bt_nsort_clicked()
{

        QFile PFile("Personlisttest.csv");                    //Personen einlesen, meiste kopiert von view item
        if(!PFile.open(QFile::ReadOnly| QFile::Text))
        {
            QMessageBox ErrorMsg;
            ErrorMsg.setText("Lesen von Personlist nicht möglich");
            ErrorMsg.exec();
            // return;
        }
        int i=0;
        QString tmp;
        person persons[1000];    //1000 Einträge max
        QTextStream in(&PFile);
        while(!in.atEnd())
        {
            tmp = in.readLine();
            QStringList Personsplit = tmp.split(QLatin1Char(','));
            persons[i].person_name=     Personsplit[0];
            persons[i].medien_name=     Personsplit[1];
            persons[i].medien_art=      Personsplit[2];
            persons[i].adress=          Personsplit[3];
            persons[i].date=            Personsplit[4];
            i++;
        }
        PFile.close();
        for(int j=0;j<i;j++)
        {
            for(int k=0;k<j;k++)
            {
                person tausch;
                QString str1=persons[j].person_name;
                QString str2=persons[k].person_name;
                int x= QString::compare(str1,str2);

                if(x<0)
                {
                    tausch = persons[j];
                    persons[j]=persons[k];
                    persons[k]= tausch;
                }
            }
        }
        int l=0;
        while(l<i)
        {
        ui->PersonView->removeRow(l);
        ui->PersonView->insertRow(l);
        ui->PersonView->setItem(l,0,new QTableWidgetItem(persons[l].person_name));
        ui->PersonView->setItem(l,1,new QTableWidgetItem(persons[l].medien_name));
        ui->PersonView->setItem(l,2,new QTableWidgetItem(persons[l].medien_art));
        ui->PersonView->setItem(l,3,new QTableWidgetItem(persons[l].adress));
        ui->PersonView->setItem(l,4,new QTableWidgetItem(persons[l].date));
        l++;
        }
}


void view_person::on_bt_nsort2_clicked()
{
    QFile PFile("Personlisttest.csv");
    if(!PFile.open(QFile::ReadOnly| QFile::Text))
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("Lesen von Personlist nicht möglich");
        ErrorMsg.exec();
        // return;
    }
    int i=0;
    QString tmp;
    person persons[1000];    //1000 Einträge max
    QTextStream in(&PFile);
    while(!in.atEnd())
    {
        tmp = in.readLine();
        QStringList Personsplit = tmp.split(QLatin1Char(','));
        persons[i].person_name=     Personsplit[0];
        persons[i].medien_name=     Personsplit[1];
        persons[i].medien_art=      Personsplit[2];
        persons[i].adress=          Personsplit[3];
        persons[i].date=            Personsplit[4];
        i++;
    }
    PFile.close();
    for(int j=0;j<i;j++)
    {
        for(int k=0;k<j;k++)
        {
            person tausch;
            QString str1=persons[j].medien_name;
            QString str2=persons[k].medien_name;
            int x= QString::compare(str1,str2);

            if(x<0)
            {
                tausch = persons[j];
                persons[j]=persons[k];
                persons[k]= tausch;
            }
        }
    }
    int l=0;
    while(l<i)
    {
    ui->PersonView->removeRow(l);
    ui->PersonView->insertRow(l);
    ui->PersonView->setItem(l,0,new QTableWidgetItem(persons[l].person_name));
    ui->PersonView->setItem(l,1,new QTableWidgetItem(persons[l].medien_name));
    ui->PersonView->setItem(l,2,new QTableWidgetItem(persons[l].medien_art));
    ui->PersonView->setItem(l,3,new QTableWidgetItem(persons[l].adress));
    ui->PersonView->setItem(l,4,new QTableWidgetItem(persons[l].date));
    l++;
    }
}


