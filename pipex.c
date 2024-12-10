/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:36:18 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/10 09:36:25 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *path, char **cmd_split, char **env)
{
	if (execve(path, cmd_split, env) == -1)
	{
		free(path);
		freesplit(cmd_split);
		perror(cmd_split[0]);
		exit (EXIT_FAILURE);
	}
}

void	child(char *file, char *cmd, char **env, int *pipefd)
{
	char	**cmd_split;
	char	*path;
	int		fd;

	close(pipefd[0]);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Cannot read input file");
		exit (EXIT_FAILURE);
	}
	cmd_split = pipex_split(cmd, ' ');
	path = find_cmd(cmd_split[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd_split[0], 2);
		ft_putendl_fd(": command not found", 2);
		freesplit(cmd_split);
		exit (127);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	execute(path, cmd_split, env);
}

void	parent(char *file, char *cmd, char **env, int *pipefd)
{
	char	**cmd_split;
	char	*path;
	int		fd;

	close(pipefd[1]);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("bash : outfile");
		exit (EXIT_FAILURE);
	}
	cmd_split = pipex_split(cmd, ' ');
	path = find_cmd(cmd_split[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd_split[0], 2);
		ft_putendl_fd(": command not found", 2);
		freesplit(cmd_split);
		exit (EXIT_FAILURE);
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	execute(path, cmd_split, env);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (ac != 5 || !av[1][1] || !av[2][1] || !av[3][1] || !av[4][1])
		return (1);
	if (pipe(pipefd) == -1)
	{
		perror("Error creating pipe");
		exit (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error creating child process");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
		child(av[1], av[2], env, pipefd);
	else if (pid != 0)
	{
		wait(NULL);
		parent(av[4], av[3], env, pipefd);
	}
	return (0);
}
