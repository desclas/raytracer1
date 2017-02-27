##
## Makefile for  in /home/mathias/Bureau/raytrace
## 
## Made by Mathias
## Login   <mathias.descoin@epitech.eu@epitech.net>
## 
## Started on  Mon Feb 27 16:22:23 2017 Mathias
## Last update Mon Feb 27 16:27:38 2017 Mathias
##

SRC	=	calc_dir_vector.c	\
		cone.c			\
		cylinder.c		\
		light.c			\
		main.c			\
		plane.c			\
		rotate.c		\
		sphere.c		\
		translate.c

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

