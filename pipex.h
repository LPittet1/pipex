/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:36:48 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/10 16:06:25 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/includes/libft.h"
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
int		heredoc(char *limiter);
#endif