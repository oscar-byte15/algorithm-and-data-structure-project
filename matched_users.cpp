#include "matched_users.h"
#include "ui_matched_users.h"
#include <QMessageBox>

QString canciones_prueba[4] = { "Baby", "Pink", "Yellow", "Picnic" };

matched_users::matched_users(QWidget *parent, Lista<QString>* users) :
    QDialog(parent),
    ui(new Ui::matched_users)
{
    ui->setupUi(this);
    this->bd_usuarios = users;
    this->amigos = new Lista<QString>();

    this->nuevo = new QPushButton("ADD");
    connect(nuevo, SIGNAL(released()), this, SLOT(add_f()));

    connect(ui->cambiar_cancion, SIGNAL(released()), this, SLOT(set_cancion()));
    connect(ui->Log_out, SIGNAL(released()), this, SLOT(close_window()));

    QStringList titulos;
    titulos<<"ID"<<"MAIL"<<"NOMBRE"<<"CANCION"<<"ARTISTA"<<"AGREGAR";
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setColumnWidth(0, 2); ui->tableWidget->setColumnWidth(5, 30);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    int r = rand() % 4;

    QString id;
    for (int i=1; i < bd_usuarios->size(); i++){
        if ("user->mail" != bd_usuarios->get_n_node(i)->mail){
            if (canciones_prueba[r] == bd_usuarios->get_n_node(i)->cancion){
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                this->nuevo = new QPushButton("ADD");
                connect(nuevo, SIGNAL(released()), this, SLOT(add_f()));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, nuevo);

                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(bd_usuarios->get_n_node(i)->id)));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(bd_usuarios->get_n_node(i)->mail));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2,new QTableWidgetItem(bd_usuarios->get_n_node(i)->nombre));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(bd_usuarios->get_n_node(i)->cancion));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(bd_usuarios->get_n_node(i)->artista));
            }
        }
    }
}

void matched_users::set_user(Node_user<QString> *user){
    this->user = user;
    ui->USERNAME->setText(user->nombre);
    ui->new_song->setText(user->cancion);
    set_cancion();
    ui->new_song->setText("Tu cancion: " + user->cancion);
}

void matched_users::set_cancion(){
    if (user->cancion != ui->new_song->text()){
        user->cancion = ui->new_song->text();
    }


    //PRODUCE LA TABLA NUEVAMENTE
    ui->tableWidget->clear();
    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    }
    QStringList titulos;
    titulos<<"ID"<<"MAIL"<<"NOMBRE"<<"CANCION"<<"ARTISTA"<<"AGREGAR";
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setColumnWidth(0, 2); ui->tableWidget->setColumnWidth(5, 30);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);


    QString id;
    for (int i=1; i < bd_usuarios->size(); i++){
        if (user->mail != bd_usuarios->get_n_node(i)->mail){
            if (user->cancion == bd_usuarios->get_n_node(i)->cancion){
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                this->nuevo = new QPushButton("ADD");
                connect(nuevo, SIGNAL(released()), this, SLOT(add_f()));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, nuevo);

                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(bd_usuarios->get_n_node(i)->id)));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(bd_usuarios->get_n_node(i)->mail));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2,new QTableWidgetItem(bd_usuarios->get_n_node(i)->nombre));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(bd_usuarios->get_n_node(i)->cancion));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(bd_usuarios->get_n_node(i)->artista));
            }
        }   
    }
}

Lista<QString>*  matched_users::get_amigos(){
    return this->amigos;
}

void matched_users::close_window(){
    this->close();
}

void matched_users::add_f(){
    long long contador = 0;

    while(contador < ui->tableWidget->rowCount()){
        if (ui->tableWidget->currentRow() == contador){
            long long _id = ui->tableWidget->item(contador, 0)->text().toLongLong();
            QString _mail = ui->tableWidget->item(contador, 1)->text();
            QString _nombre= ui->tableWidget->item(contador, 2)->text();
            QString _contra = "********";
            QString _cancion = ui->tableWidget->item(contador, 3)->text();
            QString _artista = ui->tableWidget->item(contador, 4)->text();

            Node_user<QString>* new_f = new Node_user<QString>(_mail, _nombre, _contra, _cancion, _artista, _id);

            bool insertar = true;

            for (int i=0; i < amigos->size(); i++){
                if (amigos->get_n_node(i)->mail == _mail){
                  insertar = false;
                }
            }

            QString a = a.number(user->id);
            QString b = b.number(new_f->id);
            QString entry = "\n" + a + "\t" + b;
            if (insertar)setdatos(entry);
        }

        contador++;
    }


    QMessageBox::information(this,"AMIGOS", "AMIGO GUARDADO");
}

void matched_users::setdatos(QString renglon){
    QString contAnt;
    QString contAct;
    QFile log("followers.txt");
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
        escribir<<renglon;
        log.close();
    }

    //obtener lo utlimo que se ha escrito
    if(log.open(QIODevice::ReadOnly)){
        QTextStream leer(&log);
        contAct.append(leer.readAll());
        log.close();
    }
}
matched_users::~matched_users()
{
    delete ui;
}

