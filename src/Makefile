NAME = dbrealestate

CC = g++

SRCDIR = src

FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

RM = rm -rf

SRC = src/*.cpp

OBJ = obj/*.o

all: $(NAME)
	@echo "MAKE ALL IS DONE"

$(NAME):
	@ g++ -Wall -I/usr/include/cppconn -o $(NAME) main.cpp -L/usr/lib -lmysqlcppconn
	@sh ../cmd/cp.sh main.cpp $(NAME)

clean:
	@$(RM) $(NAME)
	@echo "MAKE CLEAN IS DONE"

re: clean all
	@echo "MAKE RE IS DONE"

.PHONY: clean
