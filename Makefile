##
## EPITECH - PROJECT, 2025
## my_plumber
## File description:
## Makefile
##

NAME =	myplumber

SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

all: $(OBJ)
	g++ -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f *~

fclean:	clean
	rm -f $(NAME)

re: fclean
	make

now:
	fclean
	make
	./${NAME}
