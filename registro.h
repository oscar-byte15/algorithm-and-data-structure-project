#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>
#include "Lista.h"

namespace Ui {
class Registro;
}

class Registro : public QDialog
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = nullptr, Lista<QString>* usuarios = nullptr);
    void set_Datos(QString renglon);
    bool agregar_usuario();

    ~Registro();

private:
    Ui::Registro *ui;
    Lista<QString>* bd_usuarios;

private slots:
    void completar_registro();
    void cerrar_registro();
};

#endif // REGISTRO_H
