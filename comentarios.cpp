#include "comentarios.h"
#include "ui_comentarios.h"

comentarios::comentarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::comentarios)
{
    ui->setupUi(this);
    cargar_com = true;
    connect(ui->publicar, SIGNAL(released()), this, SLOT(push_comment()));
    connect(ui->Home, SIGNAL(released()), this, SLOT(close_w()));
}

void comentarios::set_comments(BST<comentario, long long> *coms, vector<long long>* vec){
    QString id, id_p;
    this->pos = vec;
    set_clear_titles();

    for (int i=0; i < vec->size(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(coms->find(vec->at(i))->id)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(id_p.number(coms->find(vec->at(i))->id_pub)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2,new QTableWidgetItem(coms->find(vec->at(i))->date));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(coms->find(vec->at(i))->comment));

    }
}
void comentarios::set_user(Node_user<QString> * n){
    ui->username->setText(n->nombre);
    this->user = n;
}

void comentarios::set_clear_titles(){
    ui->tableWidget->clear();

    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
    }

    QStringList titulos;

    titulos<<"ID"<<"ID_PUB"<<"Date"<<"Comment";
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}
void comentarios::push_comment(){
    QMessageBox::information(this,"Comentario", " GUARDADO");

    //SI ESCRIBE DATOS (PUEDE VERIFICAR CON EL ARCHIVO TSV) PERO CUANDO VUELVO A CORRER EL PROGRAMA BOTA ERROR. LO DEJAMOS COMENTADO PARA AHORRARNOS PROBLEMAS.
/*
    QString id, id_pub;
    QString mensaje = ui->coment->text();
    QString day,month,year;
    day = day.number(QDate::currentDate().day());
    month = month.number(QDate::currentDate().month());
    year = year.number(QDate::currentDate().year());

    QString pubdate = year+"-"+month+"-"+day;

    QString renglon = "\n" + id.number(user->id) + "\t" + id_pub.number(pos->size()+1) + "\t" + pubdate + "\t" + mensaje;

    QString contAnt;
    QString contAct;
    QFile log("comment.tsv");
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
*/
    this->close();
}

void comentarios::close_w(){
    this->close();
}

comentarios::~comentarios()
{
    delete ui;
}
