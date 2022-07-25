/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/07/25 19:09:54 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				exit (0);
			return (paths);
		}
		i++;
		paths = NULL;
	}
	return (0);
}

void	get_cmd(struct s_d *d, char *cmd, int argc)
{
	char	*tmp;
	int		i;

	i = 0;
	d->cmd1 = ft_split(cmd, ' ');
	if (!d->cmd1 || !d->cmd1[0])
		exit (0);
	if (access(d->cmd1[0], X_OK) > -1)
		return ;
	d->cmd1[0] = ft_sjf("/", d->cmd1[0], 0);
	err_chk(0, 0, d->cmd1[0]);
	tmp = ft_sjf("", d->cmd1[0], 2);
	err_chk(0, 0, tmp);
	while (d->paths[i])
	{
		d->cmd1[0] = ft_sjf(d->paths[i], tmp, 0);
		err_chk(0, 0, d->cmd1[0]);
		if (access(d->cmd1[0], X_OK) > -1)
			break ;
		free (d->cmd1[0]);
		i++;
	}
	free (tmp);
	if (d->i == argc - 3 && access(d->cmd1[0], X_OK) == -1)
		err_chk(-1, 0, "");
}

static int	heredoc(char **argv, struct s_d *d)
{
	char	**gnl;

	if (ft_strncmp(argv[1], "here_doc", 8 + 1) == 0)
	{
		err_chk(pipe(d->pipe[0]), 0, "");
		gnl = malloc (sizeof(char **) * 2);
		if (!gnl)
			exit(0);
		while (1)
		{
			if (get_next_line(0, gnl) == -1 || ft_strncmp (gnl[0], argv[2],
					ft_strlen (argv[2]) + 1) == 0)
			{
				free(gnl[0]);
				free(gnl);
				break ;
			}
			write(d->pipe[0][IN], gnl[0], ft_strlen(gnl[0]));
			free(gnl[0]);
			write(d->pipe[0][IN], "\n", 1);
		}
		close(d->pipe[0][IN]);
		return (1);
	}
	return (0);
}

void	pipex(struct s_d *d, int argc)
{
	if (d->id == 0)
	{
		if (d->i == 1)
		{
			err_chk(dup2(d->fd1, S_IN), 1, "");
			err_chk(dup2(d->pipe[(d->i + 1) % 2][IN], S_OUT), 1, "");
		}
		else if (d->i < argc - 3)
		{
			err_chk(dup2(d->pipe[d->i % 2][OUT], S_IN), 1, "");
			err_chk(dup2(d->pipe[(d->i + 1) % 2][IN], S_OUT), 1, "");
		}
		else
		{
			err_chk(dup2(d->fd2, S_OUT), 1, "");
			err_chk(dup2(d->pipe[d->i % 2][OUT], S_IN), 1, "");
		}
		execve(d->cmd1[0], d->cmd1, NULL);
	}
	close (d->pipe[d->i % 2][OUT]);
	close (d->pipe[(d->i + 1) % 2][IN]);
}

int	main(int argc, char **argv, char **envp)
{
	struct s_d	d;

	d.i = 0;
	d.i += heredoc(argv, &d);
	d.fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d.fd2 < 1 || argc < 5)
		exit (1);
	if (d.i == 0)
	{
		d.fd1 = open(argv[1], O_RDONLY);
		err_chk (d.fd1, 1, "");
	}
	d.paths = get_paths(envp);
	while (d.i < argc - 3)
	{
		d.i++;
		err_chk(pipe(d.pipe[(d.i + 1) % 2]), 1, "");
		d.id = fork();
		err_chk(d.id, 1, "");
		get_cmd(&d, argv[1 + d.i], argc);
		pipex(&d, argc);
	}
	close (d.pipe[(d.i + 1) % 2][OUT]);
	waitpid(d.id, &d.i, 0);
	exit (WEXITSTATUS(d.i));
}
