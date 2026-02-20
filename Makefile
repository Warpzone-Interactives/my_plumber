##
## EPITECH - PROJECT, 2025
## my_plumber
## File description:
## Makefile
##

## x86_64-w64-mingw32-g++
CC	=	g++

LIB_NAME	=	libmy.a

LIB_SRC	=	player/player.cpp	\
		block/block.cpp	\
		game/game.cpp	\
		gameClock/gameClock.cpp	\

FLAG_LIB	=	-L./ -lmy

LIB_OBJ	=	$(LIB_SRC:.cpp=.o)

NAME =	myplumber

SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS	=	-I./include -I./player -I./game -I./block -I./gameClock -g

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

windows :
	$(CC) -o my_plumber.exe $(SRC) $(LIB_SRC) $(FLAG_LIB) $(FLAG_SFML)

now:clean	\
	$(OBJ)	\
	$(LIB_OBJ)
	@ar rc $(LIB_NAME) $(LIB_OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_SFML)
	@echo "\033[1;33mGood Luck\033[0;0m"
	@sleep 0.1
	@./${NAME} testmap/1-1.txt
	@rm $(NAME)

pipe:$(OBJ)	\
	$(LIB_OBJ)
	@ar rc $(LIB_NAME) $(LIB_OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_SFML)
	@./${NAME} testmap/pipeTest.txt
	@./${NAME} testmap/robustness.txt

vnow:$(OBJ)	\
	$(LIB_OBJ)
	@ar rc $(LIB_NAME) $(LIB_OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_SFML)
	@valgrind ./${NAME} testmap/pipeTest.txt

test:clean	\
	$(OBJ)	\
	$(LIB_OBJ)
	@ar rc $(LIB_NAME) $(LIB_OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_SFML)
	@./${NAME} testmap/text_test/ow
	@./${NAME} testmap/text_test/ug
	@./${NAME} testmap/text_test/castel
	@./${NAME} testmap/text_test/uw
