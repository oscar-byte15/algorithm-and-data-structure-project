#include "registro.h"
#include "ui_registro.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Registro::Registro(QWidget *parent, Lista<QString>* usuarios) :
    QDialog(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);

    //Inicializamos la base de datos de usuarios que estara manejada inicialmente por una Lista
    this->bd_usuarios = usuarios;

    //Conectamos los botones con su correspondiente funcion
    connect(ui->registrar, SIGNAL(released()), this, SLOT(completar_registro()));
    connect(ui->cerrar, SIGNAL(released()), this, SLOT(cerrar_registro()));
}

void Registro::completar_registro(){
    if (!agregar_usuario()) {
        QMessageBox::critical(this,"ERROR","Usuario ya registrado");
    }
    else  {
        Node_user<QString>* nuevo_usuario = new Node_user<QString>(ui->reg_mail->text(), ui->reg_nombre->text(), ui->reg_password->text(), ui->reg_cancion->text(), ui->reg_artista->text(), bd_usuarios->size()+1);
        QMessageBox::information(this,"REGISTRADO","REGISTRO EXITOSO");
        bd_usuarios->insertarAlFinal(nuevo_usuario);

        QString nd;
        QString id = id.number(this->bd_usuarios->size());

        nd.append("       REGISTRO      ");nd.append("\r\n");

        nd.append("MAIL     :    ");nd.append(ui->reg_mail->text());nd.append("\r\n");
        nd.append("NOMBRE   :    ");nd.append(ui->reg_nombre->text());nd.append("\r\n");
        nd.append("CONTRASEÑA :    ");nd.append(ui->reg_password->text());nd.append("\r\n");
        nd.append("CANCION  :    ");nd.append(ui->reg_cancion->text());nd.append("\r\n");
        nd.append("ARTISTA  :    ");nd.append(ui->reg_artista->text());nd.append("\r\n");
        nd.append("ID  :    ");nd.append(id);nd.append("\r\n");
        set_Datos(nd);

        ui->reg_artista->clear(); ui->reg_cancion->clear(); ui->reg_mail->clear(); ui->reg_nombre->clear(); ui->reg_password->clear();
        this->close();
    }

}

void Registro::set_Datos(QString renglon){
        QString contAnt;
        QString contAct;
        QFile log("BD_USUARIOS.txt");
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

void Registro::cerrar_registro(){
    ui->reg_artista->clear(); ui->reg_cancion->clear(); ui->reg_mail->clear(); ui->reg_nombre->clear(); ui->reg_password->clear();
    this->close();
}

bool Registro::agregar_usuario(){
    for (int i=0; i < this->bd_usuarios->size(); i++){
        if (ui->reg_mail->text() == bd_usuarios->get_n_node(i)->mail){
            return false;
        }
    }
    return true;
}

Registro::~Registro()
{
    delete ui;
}
