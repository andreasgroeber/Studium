/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#include "item.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

item::item()
{

}

void item::putdata()
{
    QFile IFile("Itemlisttest.csv");
    if(IFile.open(QFile::Append|QFile::Text))
    {
        QTextStream stream(&IFile);
        stream << this->    Name + "," +
                  this->    Autor+ "," +
                  this->    Art + "," +
                  this->    Anzahl+ "," +
                  this->    Verfuegbar+ "," +
                  '\n';

        IFile.flush();
        IFile.close();
    }
    else
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("schreiben in itemlist nicht möglich");
        ErrorMsg.exec();
    }
}
