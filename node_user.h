#ifndef NODE_USER_H
#define NODE_USER_H
#include <QString>
#include <QDate>
#include <QTextStream>


template<class T_variable>
struct Node_user {
    //Constructor Nodo usuario
    Node_user(T_variable, T_variable, T_variable, T_variable, T_variable,long long);

    //variables para mis atributos de usuario(QSTRINGS)
    T_variable mail;
    T_variable nombre;
    T_variable contra;
    T_variable cancion;
    T_variable artista;
    long long id;

    Node_user* siguiente;
    void setcancion(T_variable new_cancion){ cancion = new_cancion;}
};

template<typename T_var>
Node_user<T_var>::Node_user(T_var _mail, T_var nombre, T_var contra, T_var cancion, T_var artista,  long long _id) {
    this->mail = _mail;
    this->nombre = nombre;
    this->contra = contra;
    this->cancion = cancion;
    this->artista = artista;
    this->id = _id;
    siguiente = nullptr;
}



// OBJETO PUBLICACION

template <typename T>
struct Post{
    Post(long long, long long, T, T);
    Post(long long, long long, T, T, T, long long);

    long long id;
    long long user_id;
    T titulo;
    T mensaje;
    T pubdate;
    long long numlikes;
};

template <typename T>
Post<T>::Post(long long _id, long long _user_id, T _titulo, T _mensaje){
    this->id = _id;
    this->user_id = _user_id;
    this->titulo = _titulo;
    this->mensaje = _mensaje;
    this->numlikes = 0;

    //fecha de hoy al momento de hacer una nueva publicacion
    QString day,month,year;
    day = day.number(QDate::currentDate().day());
    month = month.number(QDate::currentDate().month());
    year = year.number(QDate::currentDate().year());
    this->pubdate = day+"/"+month+"/"+year;
}

template <typename T>
Post<T>::Post(long long _id, long long _user_id, T _titulo, T _mensaje, T _pubdate,long long _numlikes){
    this->id = _id;
    this->user_id = _user_id;
    this->mensaje = _mensaje;
    this->titulo = _titulo;
    this->mensaje = _mensaje;
    this->pubdate   = _pubdate;
    this->numlikes = _numlikes;
}


struct Interaction{
    long long id;
    long long id_pub;
    QString date;
    bool shared;
    Interaction(long long _id, long long _id_pub, QString _date, QString _shared){
        if (_shared == "FALSE"){
            shared = false;
        } else shared = true;

        id = _id;
        id_pub = _id_pub;
        date = _date;
    }
};

struct comentario {
    long long id;
    long long id_pub;
    QString date;
    QString comment;
    comentario(long long _id, long long _id_pub,QString _date, QString _comment){
        id = _id;
        id_pub = _id_pub;
        date = _date;
        comment = _comment;
    }
};


#endif // NODE_USER_H
