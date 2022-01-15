#pragma once

#include <iostream> 
#include <string>
#include <pqxx/pqxx>
#include <memory>

class Database
{
public:
    Database(std::string dbName = "", std::string user = "", std::string pass = "", std::string hostaddr = "", std::string port = "");
    ~Database();

    void connect();
    void sendQuery(std::string request);

private:
    std::string m_dbName, m_user, m_password, m_hostAddres, m_port;

    bool m_DBisConnected;
    std::unique_ptr<pqxx::connection> m_connection;

};


