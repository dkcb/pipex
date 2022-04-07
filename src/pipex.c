/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/04/07 18:23:39 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
void pipex(int fd1, int fd2, char** argv, char** envp)
{
	// execve(0);
	if (fd1 < 0 || fd2 < 0 || !envp)
		exit(0);
	printf ("%s", argv[1]);
	// return (0);
}
