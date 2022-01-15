#include "../include/database.h"

// using namespace pqxx;

int main()
{
    std::cout << "Starting DB app...\n";
    Database db;
    db.connect();
    db.sendQuery("Select * from customer;");

    // connection C;


}
