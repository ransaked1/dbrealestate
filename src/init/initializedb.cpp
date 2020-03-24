#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define DATABASE_HOST "tcp://127.0.0.1:3306"
#define DATABASE_USER "root"
#define DATABASE_PASS "root"
#define DATABASE "test"

using namespace std;

vector<vector<string>> parseCSV(string str)
{
    ifstream  data(str);
    string line;
    vector<vector<string>> parsedCsv;
    while(getline(data,line))
    {
        stringstream lineStream(line);
        string cell;
        vector<string> parsedRow;
        while(getline(lineStream,cell,','))
        {
            parsedRow.push_back(cell);
        }

        parsedCsv.push_back(parsedRow);
    }
    return parsedCsv;
};

void print(vector<vector<string>> vec) {
for (int i = 0; i < vec.size(); i++)
{
    for (int j = 0; j < vec[i].size(); j++)
    {
        cout << vec[i][j];
    }
}
}

int initDB(void)
{
cout << endl;

try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  vector<vector<string>> streets = parseCSV("csv/streets.csv");
  vector<string> street = streets[1];

  int n = street.size();
  string streetarray[n+1];
  for (int i = 0; i <= n; i++)
    streetarray[i] = street[i];

  cout<< streets.size() << endl;
  //print(streets);
  //sql::ResultSet *res;
  sql::PreparedStatement *pstmt;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect(DATABASE_HOST, DATABASE_USER, DATABASE_PASS);

  /* Connect to the MySQL test database */
  con->setSchema(DATABASE);

  stmt = con->createStatement();
  stmt->execute("DROP TABLE IF EXISTS streets");
  stmt->execute("CREATE TABLE streets("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"name   VARCHAR(56)  NOT NULL);");
	cout << "Table streets created" << endl;

	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS clients");
	stmt->execute("CREATE TABLE clients("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"name         VARCHAR(56) NOT NULL,"
		"email        VARCHAR(56) NOT NULL,"
		"phone_number VARCHAR(56) NOT NULL);");
	cout << "Table clients created" << endl;

	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS property");
	stmt->execute("CREATE TABLE property("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"surface    INT   NOT NULL,"
		"street_id  INT   NOT NULL,"
		"street_num INT   NOT NULL);");
	cout << "Table property created" << endl;

	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS rent");
	stmt->execute("CREATE TABLE rent("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"client_id 		INT	  NOT NULL,"
		"property_id	INT   NOT NULL,"
		"rent_start		DATE  NOT NULL,"
		"rent_end			DATE  NOT NULL);");
	cout << "Table rent created" << endl;

	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS retail");
	stmt->execute("CREATE TABLE retail("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"client_id    INT         NOT NULL,"
		"property_id  INT         NOT NULL,"
		"transaction  VARCHAR(56) NOT NULL,"
		"price        INT         NOT NULL);");
	cout << "Table retail created" << endl;

  /* '?' is the supported placeholder syntax */
  /*pstmt = con->prepareStatement("INSERT INTO test(id) VALUES (?)");
  for (int i = 1; i <= 10; i++) {
    pstmt->setInt(1, i);
    pstmt->executeUpdate();
  }
  delete pstmt;*/

  pstmt = con->prepareStatement("INSERT INTO streets (name)" " VALUES (streerarray)");
  pstmt->executeUpdate();
  delete pstmt;


  delete stmt;
  delete con;

}
catch (sql::SQLException &e)
{
  cout << "# ERR: SQLException in " << __FILE__;
  cout << "(" << __FUNCTION__ << ") on line "
     << __LINE__ << endl;
  cout << "# ERR: " << e.what();
  cout << " (MySQL error code: " << e.getErrorCode();
  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

cout << endl;

return EXIT_SUCCESS;
}
