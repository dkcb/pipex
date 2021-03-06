# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 17:48:16 by dkocob        #+#    #+#                  #
#    Updated: 2022/07/25 19:49:35 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:./inc/get_next_line:
SRC			= main.c pipex.c ft_strncmp.c ft_strlcpy.c ft_split.c ft_strlen.c get_next_line.c get_next_line_utils.c
OBJ			= $(SRC:.c=.o)
NAME		= pipex
CFLAGS		= -g -fsanitize=address -Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:		$(NAME)
			./$(NAME) "infile" "cat -e" "cat" "wc -l" "cat -e" "outfile"
# ./$(NAME) "infile" "cat" "cat" "cat" "outfile"
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run
