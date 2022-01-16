#include "mainwindow.h"
#include "database.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::cout << "Starting DB app...\n";
//    Database db;
//    db.connect();
//    db.sendQuery("Select * from customer;");


    return a.exec();
}
