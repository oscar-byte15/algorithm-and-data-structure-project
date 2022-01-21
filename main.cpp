#include "m_menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    M_Menu w;
    w.show();
    return a.exec();
}


