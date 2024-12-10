/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:10:41 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/10 16:50:04 by lpittet          ###   ########.fr       */
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
	
	if (pipe(pipefd) == -1)
	{
		perror("Error creating pipe");
		exit (1);
	}
	cmd_split = pipex_split(cmd, ' ');
	path = find_path(cmd_split[0], env);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1] ,STDOUT_FILENO);
		close(pipefd[1]);
		execve(path, cmd_split, env);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fdin;
	int	fdout;

	fdout = -1;
	if (ac < 5)
	{
		//print usage
		return (1);
	}
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		i = 3;
		heredoc(av[2]);
		fdin = open("here_doc", O_RDONLY);
		fdout = open(av[ac -1], O_CREAT | O_APPEND | O_WRONLY , 0644);
		dup2(fdin, STDIN_FILENO);
	}
	else
	{
		fdin = open(av[1], O_RDONLY);
		if (fdin == -1)
		{
			perror("Cannot open fdin");
			exit (1);
		}
		i = 2;
		dup2(fdin, STDIN_FILENO);
	}
	while (i < ac - 2)
	{
		child(av[i], env);
		i++;
	}
	if (!access("here_doc", W_OK))
		unlink("here_doc");
	if (fdout == -1)
		fdout = open(av[ac -1], O_CREAT | O_TRUNC | O_WRONLY , 0644);
	dup2(fdout, STDOUT_FILENO);
	parent(av[i], env);
}
