NAME = game

CC = g++

SRCDIR = src
OBJDIR = obj

FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

RM = rm -rf

SRC = src/*.cpp

OBJ = obj/*.o

all: $(NAME)
	@echo "MAKE ALL IS DONE"

$(NAME):
	@ g++ -Wall -I/usr/include/cppconn -o dbrealestate main.cpp -L/usr/lib -lmysqlcppconn
	@sh cp.sh main.cpp dbrealestate

clean:
	@$(RM) $(OBJDIR)
	@echo "MAKE CLEAN IS DONE"

fclean: clean
	@$(RM) $(NAME)
	@echo "MAKE FCLEAN IS DONE"

re: fclean all
	@echo "MAKE RE IS DONE"

.PHONY: clean fclean
