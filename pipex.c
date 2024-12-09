/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:36:18 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/09 14:54:18 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_full_path(char *path, char *cmd)
{
	path = ft_strjoin(path, "/");
	if (!path)
		return (NULL);
	path = ft_strjoin_and_free(path, cmd);
	if (!path)
		return (NULL);
	return (path);
}

char	*find_cmd(char *cmd, char **env)
{
	char	*cmd_line;
	char	**src;
	int		i;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			cmd_line = env[i];
			break ;
		}
		i++;
	}
	cmd_line = cmd_line + 5;
	src = ft_split(cmd_line, ':');
	i = 0;
	while (src[i])
	{
		path = get_full_path(src[i], cmd);
		if (!access(path, F_OK))
		{
			freesplit(src);
			return (path);
		}
		free(path);
		i++;
	}
	freesplit(src);
	return (NULL);
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
	if (execve(path, cmd_split, env) == -1)
	{
		free(path);
		freesplit(cmd_split);
		perror(cmd);
		exit (EXIT_FAILURE);
	}
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
		exit (errno);
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
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	if (execve(path, cmd_split, env) == -1)
	{
		free(path);
		freesplit(cmd_split);
		perror(cmd);
		exit(errno);
	}
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (ac != 5 || !av[1][1] || !av[2][1] || !av[3][1] || !av[4][1])
		return (1);
	(void )ac;
	if (pipe(pipefd) == -1)
	{
		perror("Error creating pipe");
		exit (errno);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error creating child process");
		exit (errno);
	}
	if (pid == 0)
		child(av[1], av[2], env, pipefd);
	if (pid != 0)
	{
		wait(NULL);
	 	parent(av[4], av[3], env, pipefd);
	}
	return (0);
}
