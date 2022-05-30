/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/05/30 12:19:27 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid

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
	int			i = 0;
	int			fdp[2];
	int			fd3;
	int			pid = 0;
	int			id1;

	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			printf("Env: %s\n", environ[i] + 5);
			paths = ft_split(environ[i] + 5, ':');
			i = 0;
			break ;
		}
		i++;
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0 || argc != 5 || !envp)
		exit(0);
	cmd1 = malloc(sizeof(char *) * 4);
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
	fd3 = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);

	if (pipe(fdp) == -1)
	{
		printf ("Pipe fails!\n");
		exit (0);
	}
	id1 = fork();
	if (id1 == -1)
	{
			printf ("Forking fails!\n");
			return (4);
	}
	if (id1 == 0)
	{
		close (fdp[0]);
		printf ("Child 1 \n\n");
		if (write (fdp[1], "C1\n", 3) == -1)
		{
			
			printf ("Write to pipe fails!\n");
			return (2);
		}
		
		close(fdp[1]);
	}
	else
	{
		wait(0);
		char s[5];
		
		close (fdp[1]);
		printf ("Child 2 \n\n");
		if (read (fdp[0], &s, sizeof(char) * 3) == -1)
		{
			printf ("Read from pipe fails!\n");
			return (3);
		}
		write(1, "E\n", 2);
		printf("Read form pipe1: %s", s);
		write(1, "F\n", 2);
		close(fdp[0]);
	}
	if (pid == 0)
	{
		// execve(argv[1], &argv[2], envp);
	}
	while(wait(NULL) != -1);
	execve(cmd1[0], cmd1, NULL);
	err = errno;
	return (0);
}
