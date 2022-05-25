/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/05/23 17:30:54 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
int	pipex(int fd1, int fd2, char** argv, char** envp)
{
	int	fdp[2];
	int	fd3;
	int	pid = 0;
	if (fd1 < 0 || fd2 < 0 || !envp)
		exit(0);
	fd3 = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);

	if (pipe(fdp) == -1)
	{
		printf ("Pipe fails!\n");
		exit (0);
	}
	int	id1 = fork();
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
	char *cmd1 = "ls - l";
	if (pid == 0)
	{
		// execve(argv[1], &argv[2], envp);
	}
	// execve(argv[1], &argv[2], envp);
	// execve(argv[1], (char *const *)cmd1, envp);
	// execve("/bin/ls", "ls", NULL);
	printf ("file1: %s\n", argv[1]);
	printf ("cmd1: %s\n", argv[2]);
	printf ("cmd2: %s\n", argv[3]);
	printf ("file2: %s\n", argv[4]);
	while(wait(NULL) != -1);
	// waitpid();
	return(0);
}
