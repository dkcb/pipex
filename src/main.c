/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 18:36:33 by dkocob        #+#    #+#                 */
/*   Updated: 2022/05/26 16:59:32 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"



// open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
// char *ft_findpath(paths, argv)
// {
// 	int	i = 0;

// 	access();
// }
int	main(int argc, char** argv, char **envp)
{
	int			fd1;
	int			fd2;
	int			err;
	char		**cmd1;
	char		**cmd2;
	extern char	**environ;
	// const char *path[] = {"ls", "-l", "inc", NULL};
	// char path[] = "ls -a";
	char		*path;
	char		**paths;
	// const char command = "ls";


	int	i = 0;
	// char		*pth;

	while (environ[i])
	{
		// if (ft_strncmp(environ[i], "PATH=", 5))
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			// printf("Env: %s\n", environ[i] + 5);
			paths = ft_split(environ[i] + 5, ':');
			i = 0;
			break ;
		}
		i++;
	}
	// while (paths[i])
	// {
	// 	printf("path[%d]: %s\n", i , paths[i]);
	// 	i++;
	// }
	i = 0;
	// cmd1 = argv[2];
	// cmd2 = argv[3];
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	// write(1, "oY!\n", 4);
	// printf("fd1 = %d, fd2 = %d, argc = %d", fd1, fd2, argc);
	if (fd1 < 0 || fd2 < 0 || argc != 5)
		exit(0);
	// cmd1 = sjf(path1, cmd1, 2);
	// if(!access(argv[2], 0) || !access(argv[3], 0))
		//exit(0); //perror("no cmd!") PATH?

	// printf ("path1: %s,\n path 2: %s\n", path[0], path[1]);
	// path = ft_findpath(paths, argv);
	while (i < 6)
	{
		// printf("argv[%d]: %s\n", i , argv[i]);
		i++;
	}
	cmd1 = malloc(sizeof(char *) * 4);
	// cmd1[0] = ft_strdup("ls");
	// cmd1[1] = ft_strdup("-l");
	// cmd1[2] = NULL;
	cmd1[0] = argv[1];
	cmd1[1] = ft_strdup("infile");
	cmd1[2] = NULL;
	// cmd1[1] = ft_strdup("/Users/dkocob/Desktop/pipex/infile");
	// cmd1[2] = ft_strdup("\0");
	execve("/bin/cat", cmd1, NULL);
	err = errno;
	// execve("/bin/ls", cmd1, NULL);

	// pipex(fd1, fd2, argv, envp);
	return (0);
}
