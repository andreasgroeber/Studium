/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#include "add_item.h"
#include "ui_add_item.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QButtonGroup>

#include "buch.h"
#include "cd.h"
#include "item.h"


add_item::add_item(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_item)
{
    ui->setupUi(this);
}

add_item::~add_item()
{
    delete ui;
}

void add_item::resetElements()
{
    ui ->line_name->clear();
    ui->line_autor->clear();
    ui->line_anzahl->clear();
    return;
}
void add_item::on_bt_add_clicked()
{
    buch b;
    cd c;
    QString check_rb;

    if(ui->rb_Buch->isChecked())
         check_rb="Buch";
    else if(ui->rb_CD->isChecked())
            check_rb="CD";
    QString I_name = ui ->line_name->text();
    QString I_autor = ui ->line_autor->text();
    QString I_anzahl = ui ->line_anzahl ->text();

    QString Content = I_name + "," + I_autor +"," +
            check_rb + "," + I_anzahl + "," + I_anzahl;

    if(check_rb=="Buch")
    {
        b.Name=I_name;
        b.Autor=I_autor;
        b.Art=check_rb;
        b.Anzahl=I_anzahl;
        b.Verfuegbar=I_anzahl;
        b.putdata();
    }
    else if(check_rb=="CD")
    {
        c.Name=I_name;
        c.Autor=I_autor;
        c.Art=check_rb;
        c.Anzahl=I_anzahl;
        c.Verfuegbar=I_anzahl ;
        c.putdata();
    }
    if(check_rb=="Buch" || check_rb=="CD")
    {
    QMessageBox showcontent;
    showcontent.setText("Datensatz:"+ Content +"wurde angelegt");
    showcontent.exec();
    }
    else
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("Keine Medientyp ausgewählt, kein Datensatz wurde erstellt");
        ErrorMsg.exec();
    }

    resetElements();
 }



