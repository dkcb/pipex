/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:37:51 by dkocob        #+#    #+#                 */
/*   Updated: 2022/08/30 19:20:59 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define OUT 0
# define IN 1
# define S_OUT 1
# define S_IN 0

struct s_d
{
	int		fd1;
	int		fd2;
	int		id;
	int		i;
	int		pipe[2][2];

	char	**paths;
	char	**cmd1;
};

int		get_next_line(int fd, char **line);
int		err_chk(int i, int t, char *s);
char	*ft_sjf(char *s1, char *s2, int f);
void	execve_error_messaging(int error, char *msg, char **cmd);

#endif
