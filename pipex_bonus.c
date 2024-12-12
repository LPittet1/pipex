/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:10:41 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/12 14:45:31 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(char *cmd, char **env)
{
	char	*path;
	char	**cmd_split;

	cmd_split = pipex_split(cmd, ' ');
	path = find_path(cmd_split[0], env);
	execve(path, cmd_split, env);
}

void	child(char *cmd, char **env)
{
	char	*path;
	char	**cmd_split;
	int		pipefd[2];
	pid_t	pid;

	try_pipe(pipefd);
	cmd_split = pipex_split(cmd, ' ');
	path = find_path(cmd_split[0], env);
	pid = try_fork();
	if (pid == 0)
	{
		try_close(pipefd[0]);
		try_dup2(pipefd[1], STDOUT_FILENO);
		try_close(pipefd[1]);
		execve(path, cmd_split, env);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	pipex_bonus(int ac, char **av, char **env, int i)
{
	int	fdout;
	
	while (i < ac - 2)
	{
		child(av[i], env);
		i++;
	}
	if (!access("here_doc", F_OK))
		try_unlink("here_doc");
	fdout = try_open(av[ac -1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	try_dup2(fdout, STDOUT_FILENO);
	parent(av[i], env);
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
