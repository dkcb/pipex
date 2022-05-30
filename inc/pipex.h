/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:37:51 by dkocob        #+#    #+#                 */
/*   Updated: 2022/05/30 18:34:51 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h"

struct s_d
{
	int		fd1;
	int		fd2;
	char	**argv;
	int		argc;
	char	**paths;
	char	**cmd1;
	char	**cmd2;
};

int	pipex(int fd1, int fd2, char** argv, char** envp);
char *ft_findpath(char *paths, char **argv);
#endif