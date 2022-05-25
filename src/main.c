/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/05/25 18:55:05 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"



// open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
int	main(int argc, char** argv, char **envp)
{
	int			fd1;
	int			fd2;
	char		*cmd1;
	char		*cmd2;
	extern char	**environ;
	const char *path[] = {"ls", "-l", "inc", NULL};
	// char path[] = "ls -a";
	// const char path = "/bin/ls";
	// const char command = "ls";


	int	i = 0;
	// char		*pth;

	while (environ[i])
	{
		// if (ft_strncmp(environ[i], "PATH=", 5))
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			printf("Env: %s\n", environ[i]);
		i++;
	}
	cmd1 = argv[2];
	cmd2 = argv[3];
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	// write(1, "oY!\n", 4);
	if (fd1 < 0 || fd2 < 0 || argc != 5)
		exit(0);
	// cmd1 = sjf(path1, cmd1, 2);
	// if(!access(argv[2], 0) || !access(argv[3], 0))
		//exit(0); //perror("no cmd!") PATH?

	// printf ("path1: %s,\n path 2: %s\n", path[0], path[1]);
	execve("/bin/ls", (char **)path, NULL);

	// pipex(fd1, fd2, argv, envp);
	return (0);
}
