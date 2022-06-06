/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:37:51 by dkocob        #+#    #+#                 */
/*   Updated: 2022/06/06 13:30:48 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h"

#define OUT 0
#define IN 1
#define S_OUT 1
#define S_IN 0
#define CUR (i + 1) % 2
#define PREV i % 2
struct s_d
{
	int		fd1;
	int		fd2;
	int		i;
	// int		pipetopipe[2];
	int		pipe[2][2];
	// int		pipe2[2];
	// int		pipe3[2];
	// int		pipe[5][2];

	int		**ppu;
	int		*ppi;
	int		*ppe;
	int		argc;
	char	**argv;
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	char	*tmp;
};

int	pipex(int fd1, int fd2, char** argv, char** envp);
char *ft_findpath(char *paths, char **argv);
#endif