/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/05/30 12:07:44 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"



// open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
// char *ft_findpath(paths, argv)
// {
// 	int	i = 0;

// 	access();
// }

char	*ft_slf(char *d, char *s, size_t len, int f)
{
	char	*t;

	if (!d || !s)
		return ((void *) 0);
	if (len == 0 || len >= ft_strlen(s))
		t = malloc(sizeof(char) * (ft_strlen(d) + ft_strlen(s) + 1));
	else
		t = malloc(sizeof(char) * (ft_strlen(d) + len + 2));
	if (!t)
		return ((void *) 0);
	ft_strlcpy(t, d, ft_strlen(d) + 1);
	if (len == 0 || len >= ft_strlen(s))
		ft_strlcpy(t + ft_strlen(d), s, ft_strlen(s) + 1);
	else
		ft_strlcpy(t + ft_strlen(d), s, len + 1);
	if (f == 1 || f == 3)
	{
		free(d);
		d = ((void *)0);
	}
	if (f == 2 || f == 3)
	{
		free(s);
		s = ((void *)0);
	}
	return (t);
}

int	main(int argc, char** argv, char **envp)
{
	int			fd1;
	int			fd2;
	int			err;
	char		**cmd1;
	char		**cmd2;
	extern char	**environ;
	char		*path;
	char		**paths;
	int	i = 0;

	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			printf("Env: %s\n", environ[i] + 5);
			paths = ft_split(environ[i] + 5, ':');
			i = 0;
			break ;
		}
		// else
		// 	paths = NULL;
		i++;
	}
	// while (paths[i])
	// {
	// 	printf("path[%d]: %s\n", i , paths[i]);
	// 	i++;
	// }
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	// write(1, "oY!\n", 4);
	// printf("fd1 = %d, fd2 = %d, argc = %d", fd1, fd2, argc);
	if (fd1 < 0 || fd2 < 0 || argc != 5)
		exit(0);
	// cmd1 = sjf(path1, cmd1, 2);
	if(access(argv[1], 0) < 0 || access(argv[4], 0) < 0)
		exit(0); //perror("no cmd!") PATH?
	cmd1 = malloc(sizeof(char *) * 4);
	// cmd1[0] = ft_slf("Yo", "argv[1]", 0, 0);
	i = 0;
	while (paths[i])
	{
		cmd1[0] = ft_slf(paths[i], ft_slf("/", argv[2], 0, 0), 0, 2);
		int acc = access(cmd1[0], X_OK);
		printf("cmd1[0] = %s, %d\n", cmd1[0], acc);
		if (acc > -1)
		{
			printf("2:cmd1[0] = %s\n", cmd1[0]);
			break ;
		}
		free (cmd1[0]);
		cmd1[0] = NULL;
		i++;
	}
	// if (cmd1)
	// {

		cmd1[1] = argv[1];
		cmd1[2] = NULL;
		execve(cmd1[0], cmd1, NULL);
	// }
	err = errno;
	// execve("/bin/ls", cmd1, NULL);

	// pipex(fd1, fd2, argv, envp);
	return (0);
}
