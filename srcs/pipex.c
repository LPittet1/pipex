/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:36:18 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/12 16:07:15 by lpittet          ###   ########.fr       */
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
	fd = try_open(file, O_RDONLY, 0);
	cmd_split = pipex_split(cmd, ' ');
	path = find_path(cmd_split[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd_split[0], 2);
		ft_putendl_fd(": command not found", 2);
		freesplit(cmd_split);
		exit (EXIT_FAILURE);
	}
	try_dup2(fd, STDIN_FILENO);
	try_dup2(pipefd[1], STDOUT_FILENO);
	try_close(fd);
	execute(path, cmd_split, env);
}

void	parent(char *file, char *cmd, char **env, int *pipefd)
{
	char	**cmd_split;
	char	*path;
	int		fd;

	close(pipefd[1]);
	fd = try_open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	cmd_split = pipex_split(cmd, ' ');
	path = find_path(cmd_split[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd_split[0], 2);
		ft_putendl_fd(": command not found", 2);
		freesplit(cmd_split);
		exit (EXIT_FAILURE);
	}
	try_dup2(pipefd[0], STDIN_FILENO);
	try_dup2(fd, STDOUT_FILENO);
	try_close (fd);
	execute(path, cmd_split, env);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (!*env || ac != 5)
	{
		write(2, "Usage ./pipex infile cmd1 cmd2 outfile", 39);
		return (1);
	}
	try_pipe(pipefd);
	pid = try_fork();
	if (pid == 0)
		child(av[1], av[2], env, pipefd);
	else if (pid != 0)
	{
		try_wait();
		parent(av[4], av[3], env, pipefd);
	}
	return (0);
}
