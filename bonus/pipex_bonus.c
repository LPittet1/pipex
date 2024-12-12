/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:10:41 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/12 16:23:06 by lpittet          ###   ########.fr       */
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

void	last_command(char *cmd, char **env)
{
	char	*path;
	char	**cmd_split;

	cmd_split = pipex_split(cmd, ' ');
	path = find_path(cmd_split[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd_split[0], 2);
		ft_putendl_fd(": command not found", 2);
		freesplit(cmd_split);
		exit (EXIT_FAILURE);
	}
	execute(path, cmd_split, env);
}

void	first_commands(char *cmd, char **env)
{
	char	*path;
	char	**cmd_split;
	int		pipefd[2];
	pid_t	pid;

	cmd_split = pipex_split(cmd, ' ');
	path = find_path(cmd_split[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd_split[0], 2);
		ft_putendl_fd(": command not found", 2);
		freesplit(cmd_split);
		exit(EXIT_FAILURE);
	}
	try_pipe(pipefd);
	pid = try_fork();
	if (pid == 0)
	{
		try_close(pipefd[0]);
		try_dup2(pipefd[1], STDOUT_FILENO);
		execute(path, cmd_split, env);
	}
	try_close(pipefd[1]);
	try_dup2(pipefd[0], STDIN_FILENO);
	try_close(pipefd[0]);
}

void	pipex_bonus(int ac, char **av, char **env, int i)
{
	int	fdout;

	while (i < ac - 2)
	{
		first_commands(av[i], env);
		i++;
	}
	if (!access("here_doc", F_OK))
		try_unlink("here_doc");
	fdout = try_open(av[ac -1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	try_dup2(fdout, STDOUT_FILENO);
	last_command(av[i], env);
}

int	main(int ac, char **av, char **env)
{
	int	fdin;

	if (ac < 5)
	{
		write(2, "Usage ./pipex_bonus infile cmd1 ... cmdn outfile\n", 50);
		return (1);
	}
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		if (ac < 6)
		{
			write(2, "arguments here_doc LIMITER cmd1 ... cmdn outfile\n", 50);
			return (1);
		}
		heredoc(ac, av, env);
	}
	else
	{
		fdin = try_open(av[1], O_RDONLY, 0);
		try_dup2(fdin, STDIN_FILENO);
		pipex_bonus(ac, av, env, 2);
	}
}
