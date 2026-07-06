/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#include "delete_item.h"
#include "ui_delete_item.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QButtonGroup>

#include "buch.h"
#include "cd.h"
#include "item.h"

delete_item::delete_item(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_item)
{
    ui->setupUi(this);
}

delete_item::~delete_item()
{
    delete ui;
}

void delete_item::resetElements()
{
    ui ->ln_loeschen->clear();
    return;
}




void delete_item::on_bt_delete_clicked()
{
    QString var_del=ui ->ln_loeschen->text();
    QString check_rb;
    if(ui->rb_book->isChecked())
         check_rb="Buch";
    else if(ui->rb_cd->isChecked())
            check_rb="CD";
    else
        check_rb="-1";
    if(check_rb=="-1")
    {
        QMessageBox errormsg;
        errormsg.setText("bitte Medium auswählen");
        errormsg.exec();
        return;
    }
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
    QFile delFile("Itemlisttest.csv");
    if(delFile.open(QFile::Append|QFile::Truncate))
    {
        for(int j=0;j<i;j++)
        {
            if(var_del==items[j].Name && check_rb == items[j].Art)
            {
            QMessageBox ausgabe;
            ausgabe.setText("gelöschtes Medium: "+ items[j].Name + items[j].Art);
            ausgabe.exec();
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
}
