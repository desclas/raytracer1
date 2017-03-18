##
## Makefile for  in /home/mathias/Bureau/save
## 
## Made by Mathias
## Login   <mathias.descoin@epitech.eu@epitech.net>
## 
## Started on  Thu Mar 16 15:14:05 2017 Mathias
## Last update Thu Mar 16 15:18:18 2017 Mathias
##

SRC	=	file1.c			\
		file2.c			\
		file3.c			\
		main.c			\
		src/calc_dir_vector.c	\
		src/cone.c		\
		src/cylinder.c		\
		src/light.c		\
		src/plane.c		\
		src/rotate.c		\
		src/sphere.c		\
		src/translate.c

OBJ	=	$(SRC:.c=.o)

NAME	=	raytracer1

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -lcsfml-graphics -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
