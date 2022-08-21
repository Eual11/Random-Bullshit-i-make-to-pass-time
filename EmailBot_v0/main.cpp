#include "emailbot.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmailBot w;
    w.setFixedSize(800,600);
    w.setWindowTitle("Email Bot");
    w.show();
    return a.exec();
}
