# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 17:48:16 by dkocob        #+#    #+#                  #
#    Updated: 2022/05/23 16:58:34 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:./inc/gnl:
SRC			= main.c pipex.c ft_strncmp.c ft_strlcpy.c 
OBJ			= $(SRC:.c=.o)
NAME		= pipex
CFLAGS		= #-Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:		$(NAME)
			./$(NAME) infile "ls -l" "wc -l" outfile

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run
