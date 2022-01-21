#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <QDialog>
#include "node_user.h"
#include "bst.h"
#include <QFile>
#include <QDate>
#include <QTextStream>

namespace Ui {
class Publicacion;
}

class Publicacion : public QDialog
{
    Q_OBJECT

public:
    explicit Publicacion(QWidget *parent = nullptr);
    void set_user(Node_user<QString>*, BST<Post<QString>,long long>*);
    ~Publicacion();

private:
    Ui::Publicacion *ui;
    Node_user<QString>* user;
    BST<Post<QString>,long long>* BST_id;



private slots:
    void close_window();
    void on_Publish_clicked();
};

#endif // PUBLICACION_H
