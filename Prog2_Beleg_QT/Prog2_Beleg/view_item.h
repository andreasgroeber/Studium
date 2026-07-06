/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#ifndef VIEW_ITEM_H
#define VIEW_ITEM_H

#include <QDialog>

namespace Ui {
class view_item;
}

class view_item : public QDialog
{
    Q_OBJECT

public:
    explicit view_item(QWidget *parent = nullptr);
    ~view_item();

private slots:
    void on_bt_Sort_clicked();

    void on_bt_Sort2_clicked();

private:
    Ui::view_item *ui;
};

#endif // VIEW_ITEM_H
