#include "../include/database.h"

Database::Database(std::string dbName, std::string user, std::string pass, std::string hostaddr, std::string port)
:   m_dbName(dbName)     
    , m_user(user)
    , m_password(pass)
    , m_hostAddres(hostaddr)
    , m_port(port)
    , m_isDBConnected(false)
{
}

Database::~Database()
{
}

void Database::connect()
{
    if (!m_isDBConnected)
    {
        try
        {
            std::string request = "";
            // request += 
            // pqxx::connection temp_conn(request);

            m_isDBConnected = true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        

    }
}