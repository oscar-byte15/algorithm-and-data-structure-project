#include "m_menu.h"
#include "ui_m_menu.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <time.h>

QString canciones[4] = { "Baby", "Pink", "Yellow", "Picnic" };
QString artistas[4] = {"JustinBieber", "Aerosmith", "ACDC", "SODAESTEREO"};

M_Menu::M_Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::M_Menu)
{
    ui->setupUi(this);
    this->bd_usuarios = new Lista<QString>();
    this->user = nullptr;
    //conectar botones con funciones
    connect(ui->registro, SIGNAL(released()), this, SLOT(abrir_registro()));
    connect(ui->login, SIGNAL(released()), this, SLOT(login()));


    QString contrasea = "1234";
    srand(time(NULL));
    int random = rand() % 4;

    //LECTURA DE DATOS
    QFile file("users.tsv");
     if(file.open(QIODevice::ReadOnly)){ //WriteOnly
         QTextStream in(&file); // in << palabras[1] << "\n";
         while(!in.atEnd()){
             QString linea = in.readLine();
             QStringList palabras = linea.split("\t");

             long long id_user = palabras[0].toLongLong();
             QString email = palabras[1];
             QString nombre = palabras[2];

             random = rand() % 4;
             Node_user<QString>* nuevo_usuario = new Node_user<QString>(email,nombre, contrasea, canciones[random], artistas[random], id_user);
             bd_usuarios->insertarAlFinal(nuevo_usuario);
         }
         file.close();
     }

    //crear las ventanas necesarias para el funcionamiento correcto
    this->u_registro = new Registro(this, bd_usuarios);
    this->feed = new m_feed(this, bd_usuarios);
}

void M_Menu::abrir_registro(){
    this->u_registro->show();
}

void M_Menu::login(){
    Node_user<QString>* puntero = bd_usuarios->obtenerElementoAlInicio();
    long long contador = 0;

    while(contador < bd_usuarios->size()){
        if (puntero->mail == ui->username->text()){
            this->user = puntero;
            this->feed->set_user(puntero, this->bd_usuarios);
            this->feed->show();
            break;
        }else {
            puntero = puntero->siguiente;
            contador++;
        }
    }

    if (contador >= bd_usuarios->size()){
        QMessageBox::information(this,"USUARIO INCORRECTO","USUARIO INCORRECTO");
    }
}

M_Menu::~M_Menu()
{
    delete ui;
}

