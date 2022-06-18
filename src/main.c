/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/06/18 15:14:30 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	err_chk(int i, int t, char *s)
{
	if (i == -1 && t == 0)
	{
		// write (2, "Pipe initialisation error!\n", 27);
		perror("Error");
		exit (0);
	}
	if (i == -1 && t == 1)
	{
		// write (2, "Dup2 error!\n", 12);
		perror("Error");
		exit (0);
	}
	if (i == -1 && t == 2)
	{
		// write (2, "Forking error!\n", 12);
		perror("Error");
		exit (0);
	}
	if (i <0  && t == 3)
	{
		write (2, "No such file or directory\n", 26);
		// perror("Error");
		exit (127);
	}
	if (!s)
		exit(0);
	return (-1);
}

char	*ft_sjf(char *s1, char *s2, int f)
{
	char	*t;

	if (!s1 || !s2)
		return ((void *) 0);
	t = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!t)
		return ((void *) 0);
	ft_strlcpy(t, s1, ft_strlen(s1) + 1);
	ft_strlcpy(t + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	if (f == 1 || f == 3)
		free(s1);
	if (f == 2 || f == 3)
		free (s2);
	return (t);
}

char	**get_paths(char **envp)
{
	int i;
	char **paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				exit (0);
			return (paths) ;
		}
		i++;
		paths = NULL;
	}
	exit (127);
}

char	**get_cmd(char **paths, char *cmd)
{
	int i = 0;
	char **result;
	char *tmp;
	int acc;

	result = ft_split(cmd, ' ');
	if(!result || !result[0])
		exit (0);
	if (access(result[0], X_OK) > -1)
			return (result);
	result[0] = ft_sjf("/", result[0], 0);
	err_chk(0, 0, result[0]);
	tmp = ft_sjf("", result[0], 2);
	err_chk(0, 0, tmp);
	i = 0;
	while (paths[i])
	{
		result[0] = ft_sjf(paths[i], tmp, 0);
		err_chk(0, 0, result[0]);
		acc = access(result[0], X_OK); //check if cmd works without paths at all
		if (acc > -1)
			break ;
		free (result[0]);
		i++;
	}
	free (tmp);
	return (result);
}

int	main(int argc, char** argv, char **envp) //if envp unset
{
	struct	s_d	d;
	int		i;
	int		hd;
	int		id;
	char	**gnl;

	i = 0;
	hd = 0;
	if (ft_strncmp(argv[1], "here_doc", 8 + 1) == 0)
	{
		d.fd1 = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		gnl = malloc (sizeof(char **));
		while (1)
		{
			if (get_next_line(0, gnl) == 0 || ft_strncmp (gnl[0], argv[2], ft_strlen (argv[2]) + 1) == 0)
			{
				free(gnl[0]);
				free(gnl);
				break ;
			}
			write(d.fd1, gnl[0], ft_strlen(gnl[0]));
			free(gnl[0]);
			write(d.fd1, "\n", 1);
		}
		close(d.fd1);
		hd = 1;
	}
	d.fd1 = open(argv[1], O_RDONLY);
	d.fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644); //append with heredoc //put check only for last cmd
	d.paths = get_paths(envp);
	err_chk (d.fd1, 3, "");
	i+= hd;
	while (i < argc - 3)
	{
		i++;
		err_chk(pipe(d.pipe[CUR]), 0, "");
		d.cmd1 = get_cmd(d.paths, argv[1 + i]); //if cmd is null just skip?
		id = fork();
		err_chk(id, 2, "");
		if (id == 0) // how to check if pipe descriptor is still open?
		{
			close(d.pipe[CUR][OUT]);
			if (i == 1 || (i == 2 && hd == 1))
			{
				err_chk(dup2(d.fd1, S_IN), 1, "");
				err_chk(dup2(d.pipe[CUR][IN], S_OUT), 1, "");
			}
			else if (i < argc - 3)
			{
				err_chk(dup2(d.pipe[PREV][OUT], S_IN), 1, "");
				err_chk(dup2(d.pipe[CUR][IN], S_OUT), 1, "");
			}
			else
			{
				close(d.pipe[PREV][IN]);
				err_chk(dup2(d.fd2, S_OUT), 1, "");
				err_chk(dup2(d.pipe[PREV][OUT], S_IN), 1, "");
			}
			close (d.pipe[CUR][IN]);
			execve(d.cmd1[0], d.cmd1, NULL); // check if it correct working with all cmd exept for last one
			perror("Error File");
		}
		if (i > 1)
			close (d.pipe[PREV][OUT]);
		close (d.pipe[CUR][IN]);
	}
	close(d.pipe[CUR][OUT]); //fcntl (fd, F_GETFD)
	unlink("here_doc");
	// while (1)
	// 	continue;
	exit (0);
}
