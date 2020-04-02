#!/bin/bash
sudo g++ -Wall -I/usr/include/cppconn -o $2 $1 -L/usr/lib -lmysqlcppconn
