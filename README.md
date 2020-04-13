# Demo Real Estate Database 
A real estate MySQL database generated using C++

## Getting Started

### Prerequisites
To create a dynamic environment for MySQL and phpMyAdmin we will use Docker. You can find how to install it on Linux in this guide: https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-18-04

To install Docker Compose type:
```
sudo apt-get install docker-compose
```

To install MySQL Connector C++ type:
```
sudo apt-get install libmysqlcppconn-dev
```

Make sure you have C++ compiler and make installed:
```
sudo apt-get install g++ make
```


### Setup
Access /cmd folder and run:
```
sudo docker-compose up -d
```

To check that everything runs smoothly type:
```
sudo docker container list
```

You should see two containers running (MySQL and phpMyAdmin). If everything worked fine you should be able to access phpMyAdmin via browser by entering http://127.1.0.0/

Access /src folder and run:
```
make
```

You can now run the database generator and input MySQL queries:
```
./dbrealestate
```

### Additional build options
Delete the dbrealestate execution file:
```
make clean
```
Rebuild the project (If you made changes to the code):
```
make re
```

## Built With
* [Docker](https://docs.docker.com/get-started/) - Container system
* [MySQL](https://dev.mysql.com/doc/) - Database environment
* [phpMyAdmin](https://docs.phpmyadmin.net/en/latest/) - Graphical inteface for the database
* [MySQL Connector](https://dev.mysql.com/doc/connector-cpp/8.0/en/) - Library used to interface between C++ and MySQL
