/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:36:18 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/03 11:28:40 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_full_path(char *path, char *cmd)
{
	path = ft_strjoin(path, "/");
	if (!path)
		return (NULL);
	path = ft_strjoin(path, cmd);
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
			return (path);
		i++;
	}
	perror("Command does not exist");
	return (NULL);
}

void	child(char *cmd, char **env)//int file,
{
	char	**cmd_plus;
	char	*path;

	cmd_plus = ft_split(cmd, ' ');
	path = find_cmd(cmd_plus[0], env);
	printf("%s", path);
}

// void	parent(int file, char *cmd, char **env)
// {
// 	char **cmd_plus;

// 	cmd_plus = ft_split(cmd, ' ');
// }

int	main(int ac, char **av, char **env)
{
	// if (ac != 5 || !av[1][1] || !av[2][1] || !av[3][1] || !av[4][1])
	// 	return (1);
	if (ac)
		ft_printf("go\n");
	child(av[1], env);
	return (0);
}