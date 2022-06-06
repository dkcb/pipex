/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/06/06 15:28:19 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	pipe_init(int i)
{
	if (i == -1)
	{
		write (2, "Pipe initialisation error!\n", 27);
		exit (0);
	}
	return (-1);
}

int	dup_set(int i)
{
	if (i == -1)
	{
		write (2, "Dup2 error!\n", 12);
		exit (0);
	}
	return (-1);
}

char	*ft_sf(char *d, char *s, size_t len, int f)
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

char **get_paths(char **envp)
{
	int i = 0;
	char **paths;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			i = 0;
			break ;
		}
		i++;
		paths = NULL;
	}
	return (paths);
}

char **get_cmd(char **paths, char *cmd)
{
	int i = 0;
	char **result;
	char *tmp;
	int acc;

	result = ft_split(cmd, ' ');
	if (!result)
		exit(0);
	result[0] = ft_slf("/", result[0], 0, 0);
	if (!result[0])
		exit(0);
	tmp = ft_slf("", result[0], 0, 2);
	if (!tmp)
		exit(0);
	i = 0;
	while (paths[i])
	{
		result[0] = ft_slf(paths[i], tmp, 0, 0);
		if (!result[0])
			exit(0);
		acc = access(result[0], X_OK);
		if (acc > -1)
			break ;
		free (result[0]);
		result[0] = NULL;
		i++;
	}
	free (tmp);
	return (result);
}

int	main(int argc, char** argv, char **envp)
{
	struct	s_d	d;
	int		i;
	int		id;

	d.argv = argv;
	d.argc = argc;
	d.paths = get_paths(envp);
	d.fd1 = open(argv[1], O_RDONLY);
	d.fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d.fd1 < 0 || d.fd2 < 0 || !envp || !d.paths)
		return (write (1, "Input Error!\n", 13));
	i = 0;
	while (i < argc - 3)
	{
		i++;
		pipe_init(pipe(d.pipe[CUR]));
		d.cmd1 = get_cmd(d.paths, argv[1 + i]);
		id = fork();
		if (id == -1)
			return (printf ("Forking fails!\n"));
		if (id == 0)
		{
			close(d.pipe[CUR][OUT]);
			if (i == 1)
			{
				dup_set(dup2(d.fd1, S_IN));
				dup_set(dup2(d.pipe[CUR][IN], S_OUT));
			}
			else if (i < argc - 3)
			{
				dup_set(dup2(d.pipe[PREV][OUT], S_IN));
				dup_set(dup2(d.pipe[CUR][IN], S_OUT));
			}
			else
			{
				close(d.pipe[PREV][IN]);
				dup_set(dup2(d.fd2, S_OUT));
				dup_set(dup2(d.pipe[PREV][OUT], S_IN));
			}
			if (i > 1)
				close (d.pipe[PREV][OUT]);
			close (d.pipe[CUR][IN]);
			execve(d.cmd1[0], d.cmd1, NULL);
			perror("Error File");
		}
		else
		{
			if (i > 1)
				close (d.pipe[PREV][OUT]);
			close (d.pipe[CUR][IN]);
		}

	}
	exit (0);
	// while (waitpid(-1, 0, WUNTRACED) != -1);
	return (0);
}
