#include "../include/database.h"

Database::Database(std::string dbName, std::string user, std::string pass, std::string hostaddr, std::string port)
:   m_dbName(dbName)     
    , m_user(user)
    , m_password(pass)
    , m_hostAddres(hostaddr)
    , m_port(port)
{
}

Database::~Database()
{
}