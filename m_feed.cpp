#include "m_feed.h"
#include "ui_m_feed.h"

m_feed::m_feed(QWidget *parent, Lista<QString>* users) :
    QDialog(parent),
    ui(new Ui::m_feed)
{
    ui->setupUi(this);

    this->usuarios = users;

    this->amigos = new Lista<QString>();

    connect(ui->filtrar_btn, SIGNAL(released()), this, SLOT(filtraje()));
    connect(ui->Home, SIGNAL(released()), this, SLOT(cerrar_sesion()));
    connect(ui->Log_out, SIGNAL(released()), this, SLOT(cerrar_sesion()));
    connect(ui->New_post, SIGNAL(released()), this, SLOT(nueva_publicacion()));
    connect(ui->Friends, SIGNAL(released()), this, SLOT(find_friends()));
    connect(ui->Amigos, SIGNAL(released()), this, SLOT(ver_amigos()));
    connect(ui->ordenar, SIGNAL(released()), this, SLOT(listar()));


    ui->combo_busqueda->addItem("Seleccionar Filtro de Busqueda");
    ui->combo_busqueda->addItem("50 con mas Likes");
    ui->combo_busqueda->addItem("50 mas recientes");
    ui->combo_busqueda->addItem("50 mas relevantes");


    ui->filtrar_box->addItem("Seleccionar Filtro");
    ui->filtrar_box->addItem("Inicia con");
    ui->filtrar_box->addItem("Finaliza con");
    ui->filtrar_box->addItem("Contenido en");
    ui->filtrar_box->addItem("No está contenido en");
    ui->filtrar_box->addItem("Igual a");

    this->comments = new comentarios;
    this->m_friends = new Amigos;
    this->posts = new Publicacion;
    this->usuarios_encontrados = new matched_users(this, this->usuarios);


    this->BST_id = new BST<Post<QString>,long long>([](Post<QString> p){return p.id;});
    this->BST_fecha = new BST<Post<QString>,QString>([](Post<QString> p){return p.pubdate;});
    this->BST_like = new BST<Post<QString>,long long>([](Post<QString> p){return p.numlikes;});
    this->BST_titulo_pub = new BST<Post<QString>,QString>([](Post<QString> p){return p.titulo;});
    this->BST_compartio = new BST<Interaction,long long>([](Interaction i){return i.id;});
    this->BST_comment = new BST<comentario,long long>([](comentario i){return i.id;});


    //Cargar publicaciones

    QFile file1("publications.tsv");
     if(file1.open(QIODevice::ReadOnly)){ //WriteOnly

        QTextStream in(&file1); // in << palabras[1] << "\n";
        QString linea = in.readLine();
        while(!in.atEnd()){
            linea = in.readLine();
            QStringList palabras = linea.split("\t");
            long long id = palabras[0].toLongLong();
            long long id_u = palabras[1].toLongLong();
            long long likes = palabras[5].toLongLong();
            Post<QString> nuevo(id,id_u,palabras[2],palabras[3],palabras[4],likes);
            this->BST_id->add(nuevo);
            this->BST_like->add(nuevo);
            this->BST_fecha->add(nuevo);
            this->BST_titulo_pub->add(nuevo);
        }
        file1.close();
    }

     cargar_escribir_Datos();
}

void m_feed::set_user(Node_user<QString>* _user, Lista<QString>* _users){
    this->user = _user;
    this->usuarios = _users;
    ui->username->setText(user->nombre);
    this->comments->set_user(this->user);
    this->posts->set_user(user, BST_id);
}
void m_feed::listar(){
    if (ui->combo_busqueda->currentText() == "50 con mas Likes"){
        this->ListarLike();
    } else if (ui->combo_busqueda->currentText() == "50 mas recientes"){
        this->Listar_Fecha();
    } else if (ui->combo_busqueda->currentText()  == "50 mas relevantes"){
        this->Listar_masRelevantes();
    } else if (ui->combo_busqueda->currentText()  == "Seleccionar Filtro de Busqueda"){
        cargar_escribir_Datos();
    }
}

void m_feed::nueva_publicacion(){
    this->posts->show();
}

void m_feed::ver_amigos(){
    this->m_friends->clear_set_amigos();
    this->m_friends->set_amigos(usuarios, user);
    this->m_friends->show();

}
void m_feed::filtraje(){
    clear_set_titles();

    if (ui->filtrar_box->currentText() == "Inicia con"){
        first_letter();
    } else if (ui->filtrar_box->currentText() == "Finaliza con"){
        last_letter();
    } else if (ui->filtrar_box->currentText()  == "Contenido en"){
        contenido_en();
    } else if (ui->filtrar_box->currentText()  == "No está contenido en"){
        no_contenido();
    }else if (ui->filtrar_box->currentText()  == "Igual a"){
        igual_a();
    }
}
void m_feed::last_letter(){
    QString id, likes;
    for(int i=1;i<BST_titulo_pub->cantidad();++i){
    QString id_pub = BST_titulo_pub->find(BST_id->find(i)->titulo)->titulo;

      if(ui->filtrar_texto->text() == id_pub.at(id_pub.size()-1))
           {
              ui->tableWidget->insertRow(ui->tableWidget->rowCount());

              QPushButton* like_btn = new QPushButton("LIKE");
              connect(like_btn, SIGNAL(released()), this, SLOT(like_post()));
              ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, like_btn);
              QPushButton* comentar = new QPushButton("COMENTAR");
              connect(comentar, SIGNAL(released()), this, SLOT(comentar()));
              ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 6, comentar);

              ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(BST_titulo_pub->find(BST_id->find(i)->titulo)->id)));
              ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->titulo));
              ui->tableWidget->setItem(ui ->tableWidget->rowCount()-1, 2,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->mensaje));
              ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->pubdate));
              ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(likes.number(BST_titulo_pub->find(BST_id->find(i)->titulo)->numlikes)));
      }
    }
}

void m_feed::contenido_en(){
    QString id, likes;
    string palabra = ui->filtrar_texto->text().toStdString();

    for (int i =1; i<BST_titulo_pub->cantidad(); i++){
        string id_pub = BST_titulo_pub->find(BST_id->find(i)->titulo)->titulo.toStdString();

        if (id_pub.find(palabra) != string::npos){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            QPushButton* like_btn = new QPushButton("LIKE");
            connect(like_btn, SIGNAL(released()), this, SLOT(like_post()));
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, like_btn);
            QPushButton* comentar = new QPushButton("COMENTAR");
            connect(comentar, SIGNAL(released()), this, SLOT(comentar()));
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 6, comentar);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(BST_titulo_pub->find(BST_id->find(i)->titulo)->id)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->titulo));
            ui->tableWidget->setItem(ui ->tableWidget->rowCount()-1, 2,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->mensaje));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->pubdate));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(likes.number(BST_titulo_pub->find(BST_id->find(i)->titulo)->numlikes)));
        }
    }
}
void m_feed::no_contenido(){
    QString id, likes;
    string palabra = ui->filtrar_texto->text().toStdString();

    for (int i =1; i<BST_titulo_pub->cantidad(); i++){
        string id_pub = BST_titulo_pub->find(BST_id->find(i)->titulo)->titulo.toStdString();

        if (id_pub.find(palabra) == string::npos){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            QPushButton* like_btn = new QPushButton("LIKE");
            connect(like_btn, SIGNAL(released()), this, SLOT(like_post()));
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, like_btn);
            QPushButton* comentar = new QPushButton("COMENTAR");
            connect(comentar, SIGNAL(released()), this, SLOT(comentar()));
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 6, comentar);

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(BST_titulo_pub->find(BST_id->find(i)->titulo)->id)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->titulo));
            ui->tableWidget->setItem(ui ->tableWidget->rowCount()-1, 2,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->mensaje));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->pubdate));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(likes.number(BST_titulo_pub->find(BST_id->find(i)->titulo)->numlikes)));
        }
    }
}
void m_feed::igual_a(){
    QString id, likes;
    QString palabra = ui->filtrar_texto->text();
    QString titulo_pub = BST_titulo_pub->find(palabra)->titulo;
    Post<QString>* nuevo = BST_titulo_pub->find(palabra);

    // A pesar de haber puesto una bandera para evitar el colapso el qt igual me manda al error. Llenar texto con todo el titulo
    bool push = false;
    if(palabra == titulo_pub){
        push = true;
    }
    if (push){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QPushButton* like_btn = new QPushButton("LIKE");
        connect(like_btn, SIGNAL(released()), this, SLOT(like_post()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, like_btn);

        QPushButton* comentar = new QPushButton("COMENTAR");
        connect(comentar, SIGNAL(released()), this, SLOT(comentar()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 6, comentar);

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(nuevo->id)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(nuevo->titulo));
        ui->tableWidget->setItem(ui ->tableWidget->rowCount()-1, 2,new QTableWidgetItem(nuevo->mensaje));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(nuevo->pubdate));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(likes.number(nuevo->numlikes)));
    }
}
void m_feed::find_friends(){
    this->usuarios_encontrados->set_user(user);
    this->usuarios_encontrados->show();
}
void m_feed::cerrar_sesion(){
    this->close();
}

void m_feed::Listar_masRelevantes()
{
    vector<Post<QString>*>* posts = new vector<Post<QString>*>();

    cargar_interactions();
    clear_set_titles();


    QString id, likes;
    long long contador =  1;
    while (contador < BST_compartio->cantidad()){
        if (BST_compartio->find(contador)->shared == true){
                 posts->push_back(BST_id->find(BST_compartio->find(contador)->id));
        }
        contador++;
    }

    for (int i =0; i < 50; i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QPushButton* like_btn = new QPushButton("LIKE");
        connect(like_btn, SIGNAL(released()), this, SLOT(like_post()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, like_btn);

        QPushButton* comentar = new QPushButton("COMENTAR");
        connect(comentar, SIGNAL(released()), this, SLOT(comentar()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 6, comentar);

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(posts->at(i)->id)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(posts->at(i)->titulo));
        ui->tableWidget->setItem(ui ->tableWidget->rowCount()-1, 2,new QTableWidgetItem(posts->at(i)->mensaje));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(posts->at(i)->pubdate));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(likes.number(posts->at(i)->numlikes)));
    }
}

void m_feed::cargar_interactions(){
    QFile file("interaction.tsv");
    if(file.open(QIODevice::ReadOnly)){ //WriteOnly
        QTextStream in(&file); // in << palabras[1] << "\n";
        QString linea = in.readLine();
        while(BST_compartio->cantidad()<1000){ // ESA CONDICION DEL WHILE DEBERIA SER UN "!in.atEnd()" PERO NO SABEMOS PORQUE NUNCA SALE DEL WHILE LOOP. Para corregirlo pusimos un limite.
            linea = in.readLine();
            QStringList palabras = linea.split("\t");
            long long id = palabras[0].toLongLong();
            long long id_pub = palabras[1].toLongLong();
            Interaction nuevo(id,id_pub,palabras[2],palabras[3]);
            BST_compartio->add(nuevo);
        }
        file.close();
    }
}

void m_feed::ListarLike(){
    clear_set_titles();
    BST_like->postorder(ui->tableWidget);
}

void m_feed::Listar_Fecha(){
    clear_set_titles();
    BST_fecha->postorder(ui->tableWidget);
}

void m_feed::first_letter(){
    QString id, likes;
    for(int i=1;i<BST_titulo_pub->cantidad();++i){
    QString id_pub = BST_titulo_pub->find(BST_id->find(i)->titulo)->titulo;
    QString info = BST_titulo_pub->find(BST_id->find(i)->titulo)->mensaje;


      if(ui->filtrar_texto->text() == id_pub.at(0))
           {
              ui->tableWidget->insertRow(ui->tableWidget->rowCount());

              QPushButton* like_btn = new QPushButton("LIKE");
              connect(like_btn, SIGNAL(released()), this, SLOT(like_post()));
              ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, like_btn);
              QPushButton* comentar = new QPushButton("COMENTAR");
              connect(comentar, SIGNAL(released()), this, SLOT(comentar()));
              ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 6, comentar);

              ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(BST_titulo_pub->find(BST_id->find(i)->titulo)->id)));
              ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->titulo));
              ui->tableWidget->setItem(ui ->tableWidget->rowCount()-1, 2,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->mensaje));
              ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(BST_titulo_pub->find(BST_id->find(i)->titulo)->pubdate));
              ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(likes.number(BST_titulo_pub->find(BST_id->find(i)->titulo)->numlikes)));
      }
    }

}

void m_feed::like_post()
{
    QString n_l = ui->tableWidget->item(ui->tableWidget->currentRow(), 4)->text();
    long long num_l = n_l.toLongLong();
    num_l++;

    QString likes;
    likes.number(num_l);
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 4, new QTableWidgetItem(likes.number(num_l)));
}

void m_feed::cargar_escribir_Datos(){
    // Escribir publicaciones
    QString id, likes;

    clear_set_titles();
    for (int i=1; i <= BST_id->cantidad(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QPushButton* like_btn = new QPushButton("LIKE");
        connect(like_btn, SIGNAL(released()), this, SLOT(like_post()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, like_btn);

        QPushButton* comentar = new QPushButton("COMENTAR");
        connect(comentar, SIGNAL(released()), this, SLOT(comentar()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 6, comentar);

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,new QTableWidgetItem(id.number(this->BST_id->find(i)->id)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,new QTableWidgetItem(this->BST_id->find(i)->titulo));
        ui->tableWidget->setItem(ui ->tableWidget->rowCount()-1, 2,new QTableWidgetItem(this->BST_id->find(i)->mensaje));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,new QTableWidgetItem(this->BST_id->find(i)->pubdate));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,new QTableWidgetItem(likes.number(this->BST_id->find(i)->numlikes)));
    }
}


void m_feed::comentar(){
    BST<comentario, long long>* aux = new BST<comentario,long long>([](comentario i){return i.id;});
    vector<long long>* vec = new vector<long long>();

    if (this->comments->cargar_com == true){
        QFile file1("comment.tsv");
         if(file1.open(QIODevice::ReadOnly)){ //WriteOnly

            QTextStream in(&file1); // in << palabras[1] << "\n";
            QString linea = in.readLine();
            while(!in.atEnd()){
                linea = in.readLine();
                QStringList palabras = linea.split("\t");
                long long id = palabras[0].toLongLong();
                long long id_u = palabras[1].toLongLong();
                comentario nuevo(id,id_u,palabras[2],palabras[3]);
                BST_comment->add(nuevo);
            }
            file1.close();
        }
        comments->cargar_com = false;
    }

    QString i_d;
     for (int i = 1; i<BST_comment->cantidad(); i++){
         if (i_d.number(BST_comment->find(i)->id_pub) == ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text()){
             aux->add(*BST_comment->find(i));
             vec->push_back(BST_comment->find(i)->id);
         }
     }
     this->comments->open();
     this->comments->set_comments(aux, vec);
}

void m_feed::clear_set_titles(){
    ui->tableWidget->clear();

    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
    }

    QStringList titulos;

    titulos<<"ID"<<"Titulo"<<"Desc"<<"PubDate"<<"NumLikes"<<"LikePub"<<"Comentar";
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setColumnWidth(0, 5); ui->tableWidget->setColumnWidth(4, 60);ui->tableWidget->setColumnWidth(5, 60);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}

m_feed::~m_feed()
{
    delete ui;
}
