/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/06/18 15:43:10 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/pipex.h"

// int	pipex(int fd1, int fd2, char** argv, char** envp)
// {
// 			// if (id == 0)
// 		// {
// 		// 	close(d.pipe[CUR][OUT]);
// 		// 	if (i == 1)
// 		// 	{
// 		// 		err_chk(dup2(d.fd1, S_IN), 1, "");
// 		// 		err_chk(dup2(d.pipe[CUR][IN], S_OUT), 1, "");
// 		// 	}
// 		// 	else if (i < argc - 3)
// 		// 	{
// 		// 		err_chk(dup2(d.pipe[PREV][OUT], S_IN), 1, "");
// 		// 		err_chk(dup2(d.pipe[CUR][IN], S_OUT), 1, "");
// 		// 	}
// 		// 	else
// 		// 	{
// 		// 		close(d.pipe[PREV][IN]);
// 		// 		err_chk(dup2(d.fd2, S_OUT), 1, "");
// 		// 		err_chk(dup2(d.pipe[PREV][OUT], S_IN), 1, "");
// 		// 	}
// 		// 	if (i > 1)
// 		// 		close (d.pipe[PREV][OUT]);
// 		// 	close (d.pipe[CUR][IN]);
// 		// 	execve(d.cmd1[0], d.cmd1, NULL);
// 		// 	perror("Error File");
// 		// }
// 	// while (waitpid(-1, 0, WUNTRACED) != -1);
// 	return(0);
// }
