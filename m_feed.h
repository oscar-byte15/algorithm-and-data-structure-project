#ifndef M_FEED_H
#define M_FEED_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <string>

#include "publicacion.h"
#include "matched_users.h"
#include "comentarios.h"

#include "Lista.h"
#include "amigos.h"
#include "bst.h"

namespace Ui {
class m_feed;
}

class m_feed : public QDialog
{
    Q_OBJECT
    Publicacion* posts;
    matched_users* usuarios_encontrados;
    Amigos* m_friends;
    comentarios* comments;

public:
    explicit m_feed(QWidget *parent = nullptr, Lista<QString>* users = nullptr);
    void set_user(Node_user<QString>*, Lista<QString>*);
    void clear_set_titles();
    ~m_feed();

private:
    Ui::m_feed *ui;

    //NODO USUARIO
    Node_user<QString>* user;

    //LISTA BASE DE DATOS DE USUARIOS Y LISTA DE AMIGOS
    Lista<QString>* usuarios;
    Lista<QString>* amigos;

    //BST para atributos de la publicacion
    BST<Post<QString>, QString>* BST_fecha;
    BST<Post<QString>, long long>* BST_like;
    BST<Post<QString>, QString>* BST_titulo_pub;
    BST<Post<QString>, long long>*BST_id;

    BST<Interaction,long long>* BST_compartio;
    BST<comentario,long long>* BST_comment;



    void Listar_masRelevantes();
    void ListarLike();
    void Listar_Fecha();
    void cargar_escribir_Datos();
    void cargar_interactions();

    void first_letter();
    void last_letter();
    void igual_a();
    void contenido_en();
    void no_contenido();



private slots:
    void nueva_publicacion();
    void find_friends();
    void ver_amigos();
    void cerrar_sesion();

    void listar();
    void filtraje();
    void like_post();

    void comentar();
};

#endif // M_FEED_H
