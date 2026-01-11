##
## EPITECH - PROJECT, 2025
## my_plumber
## File description:
## Makefile
##


CC	=	g++

LIB_NAME	=	libmy.a

LIB_SRC	=	window.cpp	\
		grid.cpp	\
		level.cpp	\
		src/get_where.cpp	\
		src/map_loading.cpp	\
		src/init_general.cpp	\

FLAG_LIB	=	-L./ -lmy

LIB_OBJ	=	$(LIB_SRC:.cpp=.o)

NAME =	myplumber

SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS	=	-I./include -Wextra -Wall

FLAG_SFML	=	-lsfml-graphics -lsfml-window -lsfml-system

all: $(OBJ)	\
	$(LIB_OBJ)
	ar rc $(LIB_NAME) $(LIB_OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_SFML)

clean:
	rm -f $(OBJ)
	rm -f $(LIB_OBJ)
	rm -f *~

fclean:	clean
	rm -f $(NAME)

re: fclean
	make

now:clean	\
	$(OBJ)	\
	$(LIB_OBJ)
	@ar rc $(LIB_NAME) $(LIB_OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_SFML)
	@echo "\033[1;33mGood Luck\033[0;0m"
	@sleep 1
	@./${NAME} testmap/1-1.txt

vnow:$(OBJ)	\
	$(LIB_OBJ)
	@ar rc $(LIB_NAME) $(LIB_OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_SFML)
	@echo "\033[1;33mGood Luck\033[0;0m"
	@sleep 1
	@valgrind ./${NAME} testmap/1-1.txt
