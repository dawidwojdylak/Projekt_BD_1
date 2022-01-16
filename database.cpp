#include "database.h"

Database::Database(QString dbName, QString user, QString pass, QString hostaddr, QString port)
:
//  m_parent(nullptr)
     m_dbName(dbName)
    , m_user(user)
    , m_password(pass)
    , m_hostAddres(hostaddr)
    , m_port(port)
    , m_DBisConnected(false)
{
//    MainWindow::log("Starting DB app...\n");

}

Database::~Database() {}
//{
//    if (m_DBisConnected)
//        m_connection -> disconnect();
////    m_parent = nullptr;
//}

void Database::connect()
{
    QString return_value = "";
    if (!m_DBisConnected)
    {
        try
        {
            std::string request = "dbname = test user = admin password = admin \
            hostaddr = 127.0.0.1 port = 5432";
            // request +=
            // pqxx::connection temp_conn(request);
            // m_connection = new pqxx::connection(request);
            m_connection = std::make_unique<pqxx::connection>(request);


            m_DBisConnected = true;

            if (m_connection -> is_open()) {
                std::cout << "Opened database successfully: " << m_connection -> dbname() << std::endl;
                return_value += "Opened database successfully: ";
                return_value += m_connection -> dbname();
                return_value += "\n";
                emit emit_log(return_value);

            } else {
                std::cout << "Can't open database" << std::endl;
//                m_parent->log("Can't open database");
//                return "Can't open database\n";
            }

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
//    return return_value;
}

void Database::sendQuery(QString request)
{
    QString return_value;
    if (m_DBisConnected)
    {
        try
        {
            pqxx::work w {*m_connection};
            pqxx::result res { w.exec(request.toStdString()) };

            for (const auto & row : res)
            {
                for (const auto & i : row)
                    std::cout << i;
            }
            std::cout << '\n';
        }
        catch (pqxx::sql_error const & e)
        {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "SQL query: " << e.query() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
        std::cout << "Data base connection is down\n";

//    return return_value;
}
