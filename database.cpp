#include "database.h"

Database::Database(QString dbName, QString user, QString pass, QString hostaddr, QString port)
:
     m_dbName(dbName)
    , m_user(user)
    , m_password(pass)
    , m_hostAddres(hostaddr)
    , m_port(port)
    , m_DBisConnected(false)
{
    emit emit_log("Starting DB app...");

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
                emit emit_log("Can't open database.\n");
            }

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            emit emit_log(e.what());
        }
    }
//    return return_value;
}

pqxx::result Database::sendQuery(QString request)
{
//    qDebug() << request;
    pqxx::result temp;
    if (m_DBisConnected)
    {
        try
        {
            pqxx::work w {*m_connection};
            pqxx::result res { w.exec(request.toStdString()) };

            for (const auto & row : res)
            {
//                for (const auto & i : row)
//                    qDebug() << i.c_str();
//                    std::cout << i;
            }
            return res;
        }
        catch (pqxx::sql_error const & e)
        {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "SQL query: " << e.query() << std::endl;
            emit emit_log(QString::fromStdString(std::string("SQL error: ") + std::string(e.what()) + std::string("SQL query: ") + std::string(e.query()) + '\n'));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            qDebug() << "exception in sndQuery";
        }
    }
    else
    {
        std::cout << "Data base connection is down\n";
        emit emit_log("Data base connection is down\n");
    }

    return temp;
}


void Database::setDBName      (QString arg) { m_dbName = arg; }
void Database::setUserName    (QString arg) { m_user = arg; }
void Database::setPasswd      (QString arg) { m_password = arg; }
void Database::setHostAddress (QString arg) { m_hostAddres = arg; }
void Database::setPort        (QString arg) { m_port = arg; }
