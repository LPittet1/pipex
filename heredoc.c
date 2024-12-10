/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:43:12 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/10 17:05:45 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	heredoc(char *limiter)
{
	int	fd;
	char *line;

	fd = open("here_doc", O_CREAT | O_APPEND | O_RDWR, 0666);
	line = get_next_line(0);
	while (line)
	{
		ft_putstr_fd(line, fd);
		if (!ft_strncmp(line, limiter, ft_strlen(line)))
			break ;
		free(line);
		line = get_next_line(0);
	}
	free(line);
	return (fd);
}

//TODO change break condition to accept only exact match