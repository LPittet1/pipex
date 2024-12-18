/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:13:24 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/10 14:33:02 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	*get_full_path(char *path, char *cmd)
{
	path = ft_strjoin(path, "/");
	if (!path)
		return (NULL);
	path = ft_strjoin_and_free(path, cmd);
	if (!path)
		return (NULL);
	return (path);
}

static	char	*search_env(char **env)
{
	int		i;
	char	*path_list;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_list = env[i];
			return (path_list + 5);
		}
		i++;
	}
	ft_putendl_fd("PATH not found", 2);
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	*path_list;
	char	**src;
	int		i;
	char	*path;

	i = 0;
	path_list = search_env(env);
	if (!path_list)
		exit(1);
	src = ft_split(path_list, ':');
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
