#include "init/initializedb.cpp"

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Connector Libraries
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// Functions reads and executes MySQL query //
void  execSQLQuery()
{
  ERROR: try {
    string query;

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    // Connecting to database
    driver = get_driver_instance();
    con = driver->connect(DATABASE_HOST, DATABASE_USER, DATABASE_PASS);
    con->setSchema(DATABASE);

    while (1)
    {
      cout << "Input SQL query to execute or press 'Ctrl + C' to exit: ";
      cin.get();
      getline(cin, query);
      stmt = con->createStatement();
      res = stmt->executeQuery(query);
      while(res->next())
          cout << res->getString(1) << endl;
    }

    delete stmt;
    delete con;
  }
    //Catch error trace
    catch (sql::SQLException &e)
    {
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ")" << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
      goto ERROR;
    }

    cout << endl;
}

// Driver function //
int main()
{
  string ans;

  cout << "Rebuild database? (Y/N): ";
  cin >> ans;
  if (ans == "Y" || ans == "y")
  {
    initDB();
    execSQLQuery();
  }
  else
    execSQLQuery();
  return 0;
}
