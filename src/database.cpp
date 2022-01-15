#include "../include/database.h"

Database::Database(std::string dbName, std::string user, std::string pass, std::string hostaddr, std::string port)
:   m_dbName(dbName)     
    , m_user(user)
    , m_password(pass)
    , m_hostAddres(hostaddr)
    , m_port(port)
    , m_isDBConnected(false)
{}

Database::~Database()
{
    if (m_isDBConnected)
        m_connection -> disconnect();
}

void Database::connect()
{
    if (!m_isDBConnected)
    {
        try
        {
            std::string request = "dbname = test user = admin password = admin \
            hostaddr = 127.0.0.1 port = 5432";
            // request += 
            // pqxx::connection temp_conn(request);
            // m_connection = new pqxx::connection(request);
            m_connection = std::make_unique<pqxx::connection>(request);

            m_isDBConnected = true;

            if (m_connection -> is_open()) {
            std::cout << "Opened database successfully: " << m_connection -> dbname() << std::endl;
            } else {
                std::cout << "Can't open database" << std::endl;
                return ;
            }

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        

    }
}