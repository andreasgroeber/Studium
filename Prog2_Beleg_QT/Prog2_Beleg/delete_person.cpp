/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#include "delete_person.h"
#include "ui_delete_person.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QButtonGroup>

#include "buch.h"
#include "cd.h"
#include "item.h"
#include "person.h"

delete_person::delete_person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_person)
{
    ui->setupUi(this);
}

delete_person::~delete_person()
{
    delete ui;
}

void delete_person::resetElements()
{
    ui ->ln_loeschen->clear();
    return;
}



void delete_person::on_loeschen_clicked()
{
    QString var_del=ui ->ln_loeschen->text();
    QString var_del2=ui->ln_itemloeschen->text();
    if(var_del=="" || var_del2=="")
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("beide Werte müssen ausgefüllt werden!");
        ErrorMsg.exec();
    }

    /*-----------------------Personen einlesen-------*/
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
    person persons[1000];
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
    /*----------------Items-einlesen---------------*/
    QFile IFile("Itemlisttest.csv");
    if(!IFile.open(QFile::ReadOnly| QFile::Text))
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("Lesen von itemlist nicht möglich");
        ErrorMsg.exec();
        // return;
    }
    int j=0;
    QString tmp2;
    item items[1000];    //1000 Einträge max
    QTextStream in2(&IFile);
    while(!in2.atEnd())
    {
        tmp2 = in2.readLine();
        QStringList Itemsplit = tmp2.split(QLatin1Char(','));
        items[j].Name=      Itemsplit[0];
        items[j].Autor=     Itemsplit[1];
        items[j].Art=       Itemsplit[2];
        items[j].Anzahl=    Itemsplit[3];
        items[j].Verfuegbar=Itemsplit[4];
        j++;
    }
    IFile.close();
    /*--------------------Person-löschen ---------*/
    QFile delFile("Personlisttest.csv");
    if(delFile.open(QFile::Append|QFile::Truncate))
    {
        for(int k=0;k<i;k++)
        {
            if(persons[k].person_name==var_del && persons[k].medien_name==var_del2)
            {
                QMessageBox ausgabe;
                ausgabe.setText("gelöschter Kunde: "+ persons[k].person_name + " mit Medium: " + persons[k].medien_name + "_" + persons[k].medien_art);
                ausgabe.exec();
            }
            else
            {
                QTextStream stream(&delFile);
                stream << persons[k].person_name + "," +
                          persons[k].medien_name + "," +
                          persons[k].medien_art +  "," +
                          persons[k].adress + "," +
                          persons[k].date + "," +
                          '\n';
            }
         }
        delFile.flush();
        delFile.close();
    }
    else
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("schreiben in itemlist nicht möglich");
        ErrorMsg.exec();
    }
    /*-----------------------Verfügbar bei Item um 1 Erhöhen falls vorhanden-----------------*/
    QFile delFile2("Itemlisttest.csv");
    if(delFile2.open(QFile::Append|QFile::Truncate))
    {
        for(int l=0;l<j;l++)
        {
            if(items[l].Name==var_del2)
            {
                int neu_verfuegbar=items[l].Verfuegbar.toInt();
                neu_verfuegbar= neu_verfuegbar+1;

                QTextStream stream(&delFile2);
                stream << items[l].Name + "," +
                          items[l].Autor+ "," +
                          items[l].Art + "," +
                          items[l].Anzahl+ "," +
                          QString::number(neu_verfuegbar)+ "," +
                          '\n';
            }
            else
            {
            QTextStream stream(&delFile2);
            stream << items[l].Name + "," +
                      items[l].Autor+ "," +
                      items[l].Art + "," +
                      items[l].Anzahl+ "," +
                      items[l].Verfuegbar+ "," +
                      '\n';
            }

        }

    delFile2.flush();
    delFile2.close();
    }
    else
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("schreiben in itemlist nicht möglich");
        ErrorMsg.exec();
    }



/*-------------------------------------------------------*/
 }
