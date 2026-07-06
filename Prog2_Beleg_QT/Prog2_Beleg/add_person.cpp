/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#include "add_person.h"
#include "ui_add_person.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QButtonGroup>

#include "person.h"
#include "item.h"
#include "buch.h"
#include "cd.h"


add_person::add_person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_person)
{
    ui->setupUi(this);
}

add_person::~add_person()
{
    delete ui;
}

void add_person::resetElements()
{
    ui ->line_pname->clear();
    ui ->line_mname->clear();
    ui ->line_adress->clear();
    ui->line_date->clear();
    return;
}


void add_person::on_bt_add_clicked()
{
    /*---------------Items-einlesen -------------*/
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
    /*-----------------Person-einlesen-----------------*/
    person p;
    QString check_rb;

    if(ui->rb_Buch->isChecked())
         check_rb="Buch";
    else if(ui->rb_CD->isChecked())
            check_rb="CD";
    else
        check_rb="-1";

    if(check_rb!="-1")
    {
    QString P_pname = ui ->line_pname->text();
    QString P_mname = ui ->line_mname->text();
    QString P_mart = check_rb;
    QString P_adress = ui ->line_adress ->text();
    QString P_date = ui ->line_date->text();

    QString Content = P_pname + "," + P_mname +
            P_mart + "," + P_adress + "," + P_date;

    p.person_name=P_pname;
    p.medien_name=P_mname;
    p.medien_art=check_rb;
    p.adress=P_adress;
    p.date=P_date;

    item itmp;

    for(int j=0;j<i;j++)
    {
        if(items[j].Name==P_mname && check_rb==items[j].Art)
        {
            itmp=items[j];
            break;
        }
        else
        {
            itmp.Name="-1";
        }
    }
    if(itmp.Name!="-1")
      {
        int neu_verfuegbar= itmp.Verfuegbar.toInt();
            if(neu_verfuegbar>0)
            {
            neu_verfuegbar  = neu_verfuegbar-1;
            itmp.Verfuegbar=QString::number(neu_verfuegbar);

            p.putdata();
            resetElements();

            QMessageBox showcontent;
            showcontent.setText("Datensatz:"+ Content +"wurde angelegt");
            showcontent.exec();

 /*----------------Verfügbar bei item um 1 Veringern ------*/
            QFile delFile("Itemlisttest.csv");
            if(delFile.open(QFile::Append|QFile::Truncate))
            {
                for(int j=0;j<i;j++)
                {
                    if(items[j].Name==P_mname && check_rb==items[j].Art)
                    {

                        QTextStream stream(&delFile);
                        stream << items[j].Name + "," +
                                  items[j].Autor+ "," +
                                  items[j].Art + "," +
                                  items[j].Anzahl+ "," +
                                  QString::number(neu_verfuegbar)+ "," +
                                  '\n';
                    }
                    else
                    {
                    QTextStream stream(&delFile);
                    stream << items[j].Name + "," +
                              items[j].Autor+ "," +
                              items[j].Art + "," +
                              items[j].Anzahl+ "," +
                              items[j].Verfuegbar+ "," +
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



 /*-------------------------------------------------------*/
            }
            else
            {
                QMessageBox Errormsg;
                Errormsg.setText(" Kein "+ p.medien_name +" als "+ p.medien_art + " verfügbar (alle ausgeliehen)");
                Errormsg.exec();
            }
         }
    else
    {
        QMessageBox Errormsg;
        Errormsg.setText(" Kein "+ p.medien_name +" als "+ p.medien_art + " vorhanden ");
        Errormsg.exec();
    }

   }
   else
        {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("Keine Medientyp ausgewählt, kein Datensatz wurde erstellt");
        ErrorMsg.exec();
        }
}
