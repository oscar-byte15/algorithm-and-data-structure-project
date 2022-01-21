#ifndef M_MENU_H
#define M_MENU_H

#include <QMainWindow>
#include <registro.h>
#include <m_feed.h>
#include "Lista.h"

QT_BEGIN_NAMESPACE
namespace Ui { class M_Menu; }
QT_END_NAMESPACE

class M_Menu : public QMainWindow
{
    Q_OBJECT
    Registro* u_registro;
    m_feed* feed;


public:
    M_Menu(QWidget *parent = nullptr);
    ~M_Menu();

private:
    Ui::M_Menu *ui;
    Lista<QString>* bd_usuarios;
    Node_user<QString>* user;

private slots:
    void abrir_registro();
    void login();

};
#endif // M_MENU_H
