##
## Makefile for  in /home/mathias/Bureau/raytrace
## 
## Made by Mathias
## Login   <mathias.descoin@epitech.eu@epitech.net>
## 
## Started on  Mon Feb 27 16:22:23 2017 Mathias
## Last update Fri Mar  3 18:35:06 2017 Mathias
##

SRC	=	src/calc_dir_vector.c	\
		src/cone.c		\
		src/cylinder.c		\
		src/light.c		\
		main.c			\
		src/plane.c		\
		src/rotate.c		\
		src/sphere.c		\
		src/translate.c		\
		file1.c			\
		file2.c			\
		file3.c

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

