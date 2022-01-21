#ifndef AMIGOS_H
#define AMIGOS_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include "node_user.h"
#include "Lista.h"
#include "bst.h"
#include <vector>

namespace Ui {
class Amigos;
}

class Amigos : public QDialog
{
    Q_OBJECT

public:
    explicit Amigos(QWidget *parent = nullptr);
    void set_amigos(Lista<QString>* _bd_usuarios, Node_user<QString>* _user);
    void set_clear_titles();
    void cargar_Datos();
    void print_table();
    void clear_set_amigos();
    ~Amigos();

private:
    Ui::Amigos *ui;
    Lista<QString>* bd_usuarios;
    vector<Node_user<QString>*>* amigos;
    vector<long long>* id_positions;
    Node_user<QString>* user;
    BST<Node_user<QString>, long long>* BST_id;


private slots:
    void close_window();
    void dlt_friend();

};

#endif // AMIGOS_H
