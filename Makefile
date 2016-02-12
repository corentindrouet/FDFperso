# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/08 14:32:27 by cdrouet           #+#    #+#              #
#    Updated: 2016/02/12 14:30:16 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = main.c \
	  fdf_init.c \
	  segment.c \
	  write_img.c \
	  affiche.c \
	  segment_2.c \
	  event.c \

BIN = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror 

MINIFLAG = -lmlx -framework OpenGL -framework Appkit

LIB = -Llibft/ -lftprintf

$(NAME) :
	gcc $(FLAG) -c $(SRC);
	gcc $(FLAG) -o $(NAME) $(SRC) $(MINIFLAG) $(LIB)

all : $(NAME)

clean :
	rm -f $(BIN)

fclean : clean
	rm -f $(NAME)

re : fclean all
