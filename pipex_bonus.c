/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:10:41 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/08 10:01:57 by lpittet          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void child(char *cmd, char **env)
{
	char	*path;
	char	**cmd_split;
	int		pipefd[2];
	pid_t	pid;
	
	cmd_split = pipex_split(cmd, ' ');
	path = find_path(cmd_split[0], env);
	dup2(pipefd[1] ,STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd_split, env);
	}
	else
	{
		wait(NULL);
		dup2(pipefd[0], STDIN_FILENO);
	}
	
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fdin;

	if (ac < 5)
	{
		//print usage
		return (1);
	}
	else if (!ft_strncmp(av[1], "here_doc", 9))
	{
		i = 3;
		heredoc(av);
		return (0);
	}
	fdin = open(av[1], O_RDONLY);
	if (fdin == -1)
	{
		perror("Cannot open fdin");
		exit (1);
	}
	else
	{
		i = 2;
		dup2(fdin, STDIN_FILENO);
		while (i < ac - 2)
		{
			child(av[i], env);
		}
	}
	wait(NULL);
	parent(av[i], av[ac - 1]);
}
