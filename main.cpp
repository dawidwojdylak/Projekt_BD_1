#include "mainwindow.h"
#include "database.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << "Starting DB app...\n";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


//    Database db;
//    db.connect();
//    db.sendQuery("Select * from customer;");


    return a.exec();
}
