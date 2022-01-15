#pragma once

#include <iostream> 
#include <string>
#include <pqxx/pqxx>

class Database
{
public:
    Database(std::string dbName = "", std::string user = "", std::string pass = "", std::string hostaddr = "", std::string port = "");
    ~Database();

    void connect();

private:
    std::string m_dbName, m_user, m_password, m_hostAddres, m_port;

    bool m_isDBConnected;
    pqxx::connection m_connection;

};


