/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tries2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:08:55 by lpittet           #+#    #+#             */
/*   Updated: 2024/12/12 13:22:39 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	try_unlink(char *file)
{
	if (unlink(file) == -1)
	{
		perror("unlink error");
		exit(EXIT_FAILURE);
	}
}

void	try_wait(void)
{
	if (wait(NULL) == -1)
	{
		perror("wait error");
		exit(EXIT_FAILURE);
	}
}
