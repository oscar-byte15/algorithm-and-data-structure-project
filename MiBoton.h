#ifndef MIBOTON_H
#define MIBOTON_H
#include <QPushButton>
#include <QTableWidget>


class MyButton : public QPushButton {
    public:
    MyButton(QString);
    QTableWidgetItem *titem;
};

MyButton::MyButton(QString string, QTableWidgetItem item){

}

#endif // MIBOTON_H
