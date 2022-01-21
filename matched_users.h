#ifndef MATCHED_USERS_H
#define MATCHED_USERS_H

#include <QDialog>
#include "Lista.h"
#include <QTableWidget>
#include <QFile>
#include <QTextStream>

namespace Ui {
class matched_users;
}

class matched_users : public QDialog
{
    Q_OBJECT

public:
    explicit matched_users(QWidget *parent = nullptr, Lista<QString>* users = nullptr);
    void set_user(Node_user<QString>*);
    Lista<QString>* get_amigos();
    void setdatos(QString);

    ~matched_users();

private:
    Ui::matched_users *ui;
    Node_user<QString>* user;
    Lista<QString>* bd_usuarios;
    Lista<QString>* amigos;
    QPushButton* nuevo;

private slots:
    void add_f();
    void set_cancion();
    void close_window();

};

#endif // MATCHED_USERS_H
