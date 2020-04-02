#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>

#include "./random.cpp"
#include "./output.cpp"

//C++ Connector Libraries
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

//Macros
#define DATABASE_HOST "tcp://127.0.0.1:3306"
#define DATABASE_USER "root"
#define DATABASE_PASS "root"
#define DATABASE "realestate"

using namespace std;

// Parse CSV files (input csv address, output bidimensional vector) //
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

// Initialize Database (Driver function) //
int initDB(void)
{
cout << endl;

try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;

  // Parse input CSVs
  vector<vector<string>> streets = parseCSV("csv/streets.csv");
  vector<vector<string>> names = parseCSV("csv/name.csv");
  vector<vector<string>> emails = parseCSV("csv/email.csv");
  vector<vector<string>> phones = parseCSV("csv/phone.csv");

  //Genetare runtime seed
  unsigned seed = gen_seed();

  //Randomize input
  shuffle(streets.begin(), streets.end(), default_random_engine(seed));
  shuffle(names.begin(), names.end(), default_random_engine(seed));
  shuffle(emails.begin(), emails.end(), default_random_engine(seed));
  shuffle(phones.begin(), phones.end(), default_random_engine(seed));


  //Starting database setup
  printProgress(0.05, "Connecting to database...       ");

  // Create a connection
  driver = get_driver_instance();
  con = driver->connect(DATABASE_HOST, DATABASE_USER, DATABASE_PASS);

  // Create MySQL database
  printProgress(0.1, "Creating realestate database...   ");
  stmt = con->createStatement();
  stmt->execute("DROP DATABASE IF EXISTS realestate");

  stmt = con->createStatement();
  stmt->execute("CREATE DATABASE IF NOT EXISTS realestate");

  // Connect to the MySQL database
  con->setSchema(DATABASE);

  // Creating tables
  printProgress(0.15, "Creating streets table...     ");
  stmt = con->createStatement();
  stmt->execute("DROP TABLE IF EXISTS streets");
  stmt->execute("CREATE TABLE streets("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"name   VARCHAR(56)  NOT NULL);");

  printProgress(0.2, "Creating clients table...   ");
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS clients");
	stmt->execute("CREATE TABLE clients("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"name         VARCHAR(56) NOT NULL,"
		"email        VARCHAR(56) NOT NULL,"
		"phone_number VARCHAR(56) NOT NULL);");

  printProgress(0.25, "Creating property table...   ");
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS property");
	stmt->execute("CREATE TABLE property("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"surface    INT           NOT NULL,"
		"street_id  INT UNSIGNED  NOT NULL,"
		"street_num INT           NOT NULL,"
    "CONSTRAINT FK_StreetID FOREIGN KEY (street_id) REFERENCES streets (id));");

  printProgress(0.3, "Creating rent table...        ");
  stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS rent");
	stmt->execute("CREATE TABLE rent("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"client_id 		INT	UNSIGNED   NOT NULL,"
		"property_id	INT UNSIGNED   NOT NULL,"
		"rent_start		DATE           NOT NULL,"
		"rent_end			DATE           NOT NULL,"
    "CONSTRAINT FK_PropertyRentID FOREIGN KEY (property_id) REFERENCES property (id),"
    "CONSTRAINT FK_ClientRentID FOREIGN KEY (client_id) REFERENCES clients (id));");

  printProgress(0.35, "Creating retail table...      ");
  stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS retail");
	stmt->execute("CREATE TABLE retail("
		"id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
		"client_id    INT UNSIGNED  NOT NULL,"
		"property_id  INT UNSIGNED  NOT NULL,"
		"transaction  VARCHAR(56)   NOT NULL,"
		"price        INT           NOT NULL,"
    "CONSTRAINT FK_PropertyRetailID FOREIGN KEY (property_id) REFERENCES property (id),"
    "CONSTRAINT FK_ClientRetailID FOREIGN KEY (client_id) REFERENCES clients (id));");


  // Inserting data into tables
  printProgress(0.4, "Inserting streets data...      ");
  for (unsigned int i = 0; i <= streets.size()-1; i++)
  {
    sql::PreparedStatement *pstmt;
    string streetadd = streets[i][0];
    pstmt = con->prepareStatement("INSERT INTO streets (name) VALUES ('" + streetadd + "')");
    pstmt->executeUpdate();
    delete pstmt;
  }

  printProgress(0.6, "Inserting clients data...      ");
  for (unsigned int i = 0; i <= names.size()-1; i++)
  {
    sql::PreparedStatement *pstmt;
    string nameadd = names[i][0];
    string emailadd = emails[i][0];
    string phoneadd = phones[i][0];
    string query = "INSERT INTO clients (name, email, phone_number) VALUES ('" + nameadd + "', '" + emailadd + "', '" + phoneadd + "')";
    pstmt = con->prepareStatement(query);
    pstmt->executeUpdate();
    delete pstmt;
  }

  printProgress(0.8, "Inserting property data...    ");
  srand(gen_seed());
  int propertycount = rand() % 100 + 100;
  for (int i = 0; i <= propertycount; i++)
  {
    sql::PreparedStatement *pstmt;
    srand(gen_seed());
    string surfaceadd = to_string(rand() % 160 + 40);
    string streetadd = to_string(rand() % streets.size() + 1);
    string numadd = to_string(rand() % 42 + 1);
    string query = "INSERT INTO property (surface, street_id, street_num) VALUES ('" + surfaceadd + "', '" + streetadd + "', '" + numadd + "')";
    pstmt = con->prepareStatement(query);
    pstmt->executeUpdate();
    delete pstmt;
  }

  printProgress(0.9, "Inserting rent data...      ");
  srand(gen_seed());
  int rentcount = rand() % 50 + 100;
  for (int i = 0; i <= rentcount; i++)
  {
    sql::PreparedStatement *pstmt;
    srand(gen_seed());
    string clientadd = to_string(rand() % names.size() + 1);
    string propertyadd = to_string(rand() % propertycount + 1);
    string rentsadd = to_string(rand() % 10 + 2000) + "-" + to_string(rand() % 12 + 1) + "-" + to_string(rand() % 28 + 1);
    string renteadd = to_string(rand() % 10 + 2010) + "-" + to_string(rand() % 12 + 1) + "-" + to_string(rand() % 28 + 1);
    string query = "INSERT INTO rent (client_id, property_id, rent_start, rent_end) VALUES ('" + clientadd + "', '" + propertyadd + "', '" + rentsadd + "', '" + renteadd + "')";
    pstmt = con->prepareStatement(query);
    pstmt->executeUpdate();
    delete pstmt;
  }

  printProgress(0.995, "Inserting retail data...     ");
  srand(gen_seed());
  int retailcount = rand() % 50 + 100;
  for (int i = 0; i <= retailcount; i++)
  {
    sql::PreparedStatement *pstmt;
    srand(gen_seed());
    string clientadd = to_string(rand() % names.size() + 1);
    string propertyadd = to_string(rand() % propertycount + 1);
    string statusadd = gen_status();
    string priceadd = to_string(rand() % 100000 + 100000);
    string query = "INSERT INTO retail (client_id, property_id, transaction, price) VALUES ('" + clientadd + "', '" + propertyadd + "', '" + statusadd + "', '" + priceadd + "')";
    pstmt = con->prepareStatement(query);
    pstmt->executeUpdate();
    delete pstmt;
  }


  //Finish up and cleanup
  printProgress(1, "DONE                            ");

  delete stmt;
  delete con;
}
  //Catch error trace
  catch (sql::SQLException &e)
  {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

cout << endl << endl;

return EXIT_SUCCESS;
}
