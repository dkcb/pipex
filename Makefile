# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 17:48:16 by dkocob        #+#    #+#                  #
#    Updated: 2022/08/28 19:55:45 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:./inc/get_next_line:
SRC			= main.c pipex.c ft_strncmp.c ft_strlcpy.c ft_split.c ft_strlen.c get_next_line.c get_next_line_utils.c
OBJ			= $(SRC:.c=.o)
NAME		= pipex
CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address 

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:		$(NAME)
			./$(NAME) "here_doc" "cat" "cat" "cat" "out"
#			./$(NAME) "infile" "ct" "ct" "ls -a" "big"
#			./$(NAME) "big" "ct" "ca" "wc -l" "out"
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run
