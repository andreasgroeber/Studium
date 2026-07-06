/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/
#ifndef ADD_ITEM_H
#define ADD_ITEM_H

#include <QDialog>

namespace Ui {
class add_item;
}

class add_item : public QDialog
{
    Q_OBJECT

public:
    explicit add_item(QWidget *parent = nullptr);
    ~add_item();
    void show(); //???????


private slots:

    void on_bt_add_clicked();

private:
    Ui::add_item *ui;
    void resetElements();

};

#endif // ADD_ITEM_H
