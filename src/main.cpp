#include "../include/database.h"

using namespace pqxx;

int main()
{
    std::cout << "Starting DB app...\n";
    // Database db;
    // db.connect();

    // connection C;


    try {
      connection C("dbname = testdb user = postgres password = cohondob \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         std::cout << "Opened database successfully: " << C.dbname() << std::endl;
      } else {
         std::cout << "Can't open database" << std::endl;
         return 1;
      }
      C.disconnect ();
   } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
      return 1;
   }
}
