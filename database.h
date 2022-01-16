#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <memory>
#include <QString>
#include <QWidget>
#include <QObject>

//#include "mainwindow.h"

class MainWindow;

class Database : public QObject
{
    Q_OBJECT
public:
    Database(QString dbName = "", QString user = "", QString pass = "", QString hostaddr = "", QString port = "");
    virtual ~Database();
//    ~Database();

    void connect();
    void sendQuery(QString request);


signals:
    void emit_log(const QString text) const;

private:
//    MainWindow * m_parent;
    QString m_dbName, m_user, m_password, m_hostAddres, m_port;
    bool m_DBisConnected;
    std::unique_ptr<pqxx::connection> m_connection;

};


#endif // DATABASE_H
