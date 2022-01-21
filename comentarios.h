#ifndef COMENTARIOS_H
#define COMENTARIOS_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "bst.h"
#include "node_user.h"

namespace Ui {
class comentarios;
}

class comentarios : public QDialog
{
    Q_OBJECT

public:
    explicit comentarios(QWidget *parent = nullptr);
    void set_comments(BST<comentario, long long>* coms, vector<long long>* vec);
    void set_user(Node_user<QString>*);
    bool cargar_com;
    void set_clear_titles();
    ~comentarios();

private:
    Ui::comentarios *ui;
    Node_user<QString>* user;
    vector<long long>* pos;

private slots:
    void close_w();
private slots:
    void push_comment();
};

#endif // COMENTARIOS_H
