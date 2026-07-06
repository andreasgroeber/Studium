/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#ifndef DELETE_ITEM_H
#define DELETE_ITEM_H

#include <QDialog>

namespace Ui {
class delete_item;
}

class delete_item : public QDialog
{
    Q_OBJECT

public:
    explicit delete_item(QWidget *parent = nullptr);
    ~delete_item();
    void resetElements();
private slots:
    void on_bt_delete_clicked();

private:
    Ui::delete_item *ui;
};

#endif // DELETE_ITEM_H
