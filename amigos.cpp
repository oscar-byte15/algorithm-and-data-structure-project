#include "amigos.h"
#include "ui_amigos.h"


Amigos::Amigos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Amigos)
{
    ui->setupUi(this);

    connect(ui->Home, SIGNAL(released()), this, SLOT(close_window()));
    this->BST_id = new BST<Node_user<QString>,long long>([](Node_user<QString> p){return p.id;});

    this->amigos = new vector<Node_user<QString>*>();
    this->id_positions = new vector<long long>();

    QStringList titulos;
    titulos<<"ID"<<"MAIL"<<"NOMBRE"<<"CANCION"<<"ARTISTA"<<"ELIMINAR";
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setColumnWidth(0, 2);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}


void Amigos::set_amigos(Lista<QString>* _bd_usuarios, Node_user<QString>* user){
    this->bd_usuarios = _bd_usuarios;

    for (int j=0; j< bd_usuarios->size(); j++){
        BST_id->add(*bd_usuarios->get_n_node(j));
    }

    this->user = user;
    ui->username->setText(user->nombre);

    set_clear_titles();
    cargar_Datos();
    clear_set_amigos();
    print_table();
}

void Amigos::set_clear_titles(){
    ui->tableWidget->clear();
    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    }

    QStringList titulos;
    titulos<<"ID"<<"MAIL"<<"NOMBRE"<<"CANCION"<<"ARTISTA"<<"ELIMINAR";
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setColumnWidth(0, 2);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

}

void Amigos::cargar_Datos(){
    //Cargar publicaciones
    while (id_positions->size()>0){
        id_positions->pop_back();
    }

    QFile file("followers.txt");
     if(file.open(QIODevice::ReadOnly)){ //WriteOnly

        QTextStream in(&file); // in << palabras[1] << "\n";
        QString linea = in.readLine();
        while(!in.atEnd()){
            linea = in.readLine();
            QStringList palabras = linea.split("\t");

            long long id = palabras[0].toLongLong();
            long long id_f = palabras[1].toLongLong();
            if (user->id == id){
                this->id_positions->push_back(id_f);
            }
        }
        file.close();
    }
}

void Amigos::print_table(){
    QString ip;

    for (long long i=0; i < amigos->size(); i++){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            QPushButton* like_btn = new QPushButton("ELIMINAR");
            connect(like_btn, SIGNAL(released()), this, SLOT(dlt_friend()));
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, like_btn);

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(ip.number(amigos->at(i)->id)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(amigos->at(i)->mail));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2,new QTableWidgetItem(amigos->at(i)->nombre));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(amigos->at(i)->cancion));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(amigos->at(i)->artista));
     }
}

void Amigos::dlt_friend(){
    long long cont = 0;

    while(cont< amigos->size()){
        if (amigos->at(cont)->mail == ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text()){
            id_positions->erase(id_positions->begin() + cont);
            break;
        }
        cont++;
    }
    set_clear_titles();
    clear_set_amigos();
    print_table();
}

void Amigos::close_window(){
    this->close();
}

void Amigos::clear_set_amigos(){
    while (amigos->size()>0){
        amigos->pop_back();
    }
    for (int i=0; i < this->id_positions->size(); i++){
        amigos->push_back(BST_id->find(id_positions->at(i)));
    }
}

Amigos::~Amigos()
{
    delete ui;
}
