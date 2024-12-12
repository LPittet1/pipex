/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:36:48 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/12 15:42:34 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>

char	**pipex_split(char const *s, char c);
char	*ft_strjoin_and_free(char *s1, char const *s2);
void	freesplit(char **tab);
char	*find_path(char *cmd, char **env);
void	heredoc(int ac, char **av, char **env);
int		max(int first, int second);
void	pipex_bonus(int ac, char **av, char **env, int i);

int		try_open(char *file, int flags, mode_t mode);
void	try_close(int fd);
void	try_dup2(int oldfd, int newfd);
pid_t	try_fork(void);
void	try_pipe(int pipefd[2]);
void	try_unlink(char *file);
void	try_wait(void);

#endif