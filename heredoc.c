/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:43:12 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/12 14:53:12 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc(int ac, char **av, char **env)
{
	int		fdin;
	char	*line;
	int		len;

	if (!access("here_doc", F_OK))
		try_unlink("here_doc");
	len = ft_strlen(av[2]);
	fdin = try_open("here_doc", O_CREAT | O_APPEND | O_WRONLY, 0666);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, av[2], max(len, ft_strlen(line) - 1)))
			break ;
		ft_putstr_fd(line, fdin);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fdin);
	try_open("here_doc", O_RDONLY, 0);
	try_dup2(fdin, STDIN_FILENO);
	pipex_bonus(ac, av, env, 3);
}

//TODO change break condition to accept only exact match