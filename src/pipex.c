/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/08/29 12:12:27 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	err_chk(int i, int t, char *s)
{
	if (!s)
		exit(0);
	if (i == -1 && t == 0)
	{
		perror("error:");
		exit (1);
	}
	if (i == -1 && t == 1)
	{
		exit (1);
	}
	return (-1);
}

int	execve_error_messaging(int error, char *msg)
{
	if (!msg)
		exit(0);
	write(2, msg, ft_strlen(msg));
	if (error == EACCES)
	{
		write(2, ": Premission denied\n", 20);
		exit(126);
	}
	else if (error == ENOENT)
		write(2, ": command not found\n", 20);
	else
		perror("");
	exit (127);
	return (0);
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
