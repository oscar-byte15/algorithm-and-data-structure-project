#include "publicacion.h"
#include "ui_publicacion.h"

Publicacion::Publicacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Publicacion)
{
    ui->setupUi(this);

    this->BST_id = new BST<Post<QString>,long long>([](Post<QString> p){return p.id;});
    connect(ui->Home, SIGNAL(released()), this, SLOT(close_window()));

}


void Publicacion::close_window(){
    this->close();
}

void Publicacion::set_user(Node_user<QString> *user, BST<Post<QString>,long long>* bst){
    this->user = user;
    this->BST_id = bst;
    ui->USERNAME->setText(user->nombre);
}

Publicacion::~Publicacion()
{
    delete ui;
}

void Publicacion::on_Publish_clicked()
{
    long long id_post = BST_id->cantidad() + 1;
    Post<QString>* nuevo = new Post<QString>(id_post, user->id, ui->titulo->text(), ui->publicacion->text());
    BST_id->add(*nuevo);

    QString i_d,i_d_u, n_l;
    QString new_post = "\n" + i_d.number(nuevo->id) + "\t"  + i_d_u.number(nuevo->user_id) + "\t"  + nuevo->titulo + "\t" + nuevo->mensaje + "\t" + nuevo->pubdate  + "\t" + n_l.number(nuevo->numlikes);
    QString contAnt;
    QString contAct;

    QFile log("publications.tsv");
    //primera lectura para obtener datos
    if(log.open(QIODevice::ReadOnly)){
        QTextStream leer(&log);
        contAnt.append(leer.readAll());
        log.close();
    }

    //escribir los datos
    if(log.open(QIODevice::WriteOnly)){
        QTextStream escribir(&log);
        escribir<<contAnt;
        escribir<<new_post;
        log.close();
    }

    //obtener lo utlimo que se ha escrito
    if(log.open(QIODevice::ReadOnly)){
        QTextStream leer(&log);
        contAct.append(leer.readAll());
        log.close();
    }
    this->close();
}
