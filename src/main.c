/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/05/30 17:06:24 by dkocob        ########   odam.nl         */
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

char **get_cmd(char **paths, char *cmd, char *file)
{
	int i = 0;
	char **result;

	result = malloc (sizeof(char*) * 3);
	while (paths[i])
	{
		result[0] = ft_slf(paths[i], ft_slf("/", cmd, 0, 0), 0, 2);
		int acc = access(result[0], X_OK);
		// printf("result[0] = %s, %d\n", result[0], acc);
		if (acc > -1)
		{
			printf("2:result[0] = %s\n", result[0]);
			break ;
		}
		free (result[0]);
		result[0] = NULL;
		i++;
	}
	result[1] = file;
	result[2] = NULL;
	return (result);

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
	int			pid = 0;
	int			id1;

	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
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
		cmd1 = get_cmd(paths, argv[2], argv[1]);
		close (fdp[0]);
		// printf ("Child %s, %s\n\n", cmd1[0], cmd1[1]);
		if (dup2 (fdp[1], 1) == -1)
		{
			printf ("Write to pipe fails!\n");
			return (2);
		}
		close(fdp[1]);
		execve(cmd1[0], cmd1, NULL);
		perror("Error Child");
	}
	else
	{
		static char buf[100 + 1];
		int rd = 0;
		
		wait(0);
		cmd2 = get_cmd(paths, argv[3], NULL);
		close (fdp[1]);
		// printf ("Main %s, %s\n\n", cmd2[0], cmd2[1]);
		if (dup2 (fdp[0], 0) == -1)
		{
			printf ("Write to stdout fails!\n");
			return (3);
		}
		if (dup2(fd2, 1) == -1);
		{
			write(2,"Read form pipe fails\n",22);
			return (5);
		}
		close(fdp[0]);
	}
	execve(cmd2[0], cmd2, NULL);
	perror("Error Main");
	return (0);
}
