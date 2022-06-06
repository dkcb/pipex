# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 17:48:16 by dkocob        #+#    #+#                  #
#    Updated: 2022/06/06 16:49:01 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:./inc/gnl:
SRC			= main.c pipex.c ft_strncmp.c ft_strlcpy.c ft_split.c ft_strdup.c ft_strlen.c
OBJ			= $(SRC:.c=.o)
NAME		= pipex
CFLAGS		= -g -fsanitize=address #-Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:		$(NAME)
			./$(NAME) "infile" "cat" "grep a" "cat" "wc -l" "outfile"
#			./$(NAME) "infile" "cat" "cat " "wc" "outfile"

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run
