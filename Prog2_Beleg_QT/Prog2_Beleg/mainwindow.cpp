/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01


Testlisten sind im extra Ordner zu finden bzw.

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "view_item.h"
#include "add_item.h"

#include "view_person.h"
#include "add_person.h"

#include "delete_item.h"
#include "delete_person.h"

#include "item.h"
#include "buch.h"
#include "cd.h"
#include "person.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*------view/add item sowie person --------*/
void MainWindow::on_bt_view_item_clicked()
{
    view_item viewitems;
    viewitems.setModal(true);
    viewitems.exec();
}

void MainWindow::on_bt_add_item_clicked()
{
    add_item additem;
    additem.setModal(true);
    additem.exec();
}

void MainWindow::on_bt_view_person_clicked()
{
    view_person viewperson;
    viewperson.setModal(true);
    viewperson.exec();
}

void MainWindow::on_bt_add_person_clicked()
{
    add_person addperson;
    addperson.setModal(true);
    addperson.exec();
}
/*--------------------searchbar interaktionen-------------------------------*/

void MainWindow::on_bt_search_item_clicked()
{
    QString search = ui ->Searchbar->text();
    //searchbar in String speichern

    QFile IFile("Itemlisttest.csv");                    //Items und Personen einlesen
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
    int j=0;
    while(j<i)
    {
        if(search==items[j].Name)
        {
            QMessageBox ausgabe;
            ausgabe.setText("Ergebnis der Suche: " + items[j].Name + "_" + items[j].Art + " " +
                               "von: "+ items[j].Autor + "  " +items[j].Verfuegbar + " von " + items[j].Anzahl + " vorhanden ");
            ausgabe.exec();
            j++;
        }
        else
        {
            j++;
        }

    }
}

void MainWindow::on_bt_search_person_clicked()
{
    QString search = ui ->Searchbar->text();
    //searchbar in String speichern

    QFile PFile("Personlisttest.csv");                    //Items und Personen einlesen
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
        QStringList personsplit = tmp.split(QLatin1Char(','));
        persons[i].person_name=      personsplit[0];
        persons[i].medien_name=     personsplit[1];
        persons[i].medien_art=       personsplit[2];
        persons[i].adress=        personsplit[3];
        persons[i].date=         personsplit[4];
        i++;
    }
    PFile.close();
    int j=0;
    while(j<i)
    {
        if(search==persons[j].person_name || search==persons[j].medien_name)
        {
            QMessageBox ausgabe;
            ausgabe.setText("Ergebnis der Suche: " + persons[j].person_name + " besitzt: " + persons[j].medien_name +
                               "_"+ persons[j].medien_art + " Adresse: " +persons[j].adress + " bis: " + persons[j].date);
            ausgabe.exec();
            j++;
        }
        else
        {
            j++;
        }

    }

}



/*-----------------delete buttons----------------------*/
void MainWindow::on_bt_delete_item_clicked()
{
    delete_item deleteitem;
    deleteitem.setModal(true);
    deleteitem.exec();
}


void MainWindow::on_bt_delete_person_clicked()
{
    delete_person deleteperson;
    deleteperson.setModal(true);
    deleteperson.exec();
}

