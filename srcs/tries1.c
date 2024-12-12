/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tries1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:41:53 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/12 16:15:42 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	try_open(char *file, int flags, mode_t mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	try_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("Close error");
		exit(EXIT_FAILURE);
	}
}

void	try_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2 error");
		exit(EXIT_FAILURE);
	}
}

pid_t	try_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	try_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
}
