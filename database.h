#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <memory>
#include <QString>
#include <QWidget>
#include <QObject>

#include <QDebug>

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
    pqxx::result sendQuery(QString request, bool saveMode = false);
    void setDBName      (QString arg);
    void setUserName    (QString arg);
    void setPasswd      (QString arg);
    void setHostAddress (QString arg);
    void setPort        (QString arg);
    void setSelectedTab (QString arg);

    QString getSelectedTab() const;
    bool isConnected() const;


signals:
    void emit_log(const QString text, bool red = false) const;

private:
//    MainWindow * m_parent;
    QString m_dbName, m_user, m_password, m_hostAddres, m_port;
    bool m_DBisConnected;
    std::unique_ptr<pqxx::connection> m_connection;
    QString m_selectedTable;

};


#endif // DATABASE_H
