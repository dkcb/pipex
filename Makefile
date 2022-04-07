# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 17:48:16 by dkocob        #+#    #+#                  #
#    Updated: 2022/04/07 15:59:02 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./libft/:
SRC			= main.c pipex.c
OBJ			= $(SRC:.c=.o)
NAME		= pipex
CFLAGS		= -Wall -Werror -Wextra

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:			$(NAME)
				./$(NAME)

clean:
				rm -f $(OBJ)

fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus run
