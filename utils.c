/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:25:11 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/18 13:13:34 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen_arg(t_pi *pip)
{
	int	i;

	i = 0;
	while (pip->arg[i])
		i++;
	return (i);
}

void	free_pip(t_pi *pip)
{
	int	i;

	i = 0;
	if (pip->pipe)
	{
		while (pip->pipe[i])
		{
			free(pip->pipe[i]);
			i++;
		}
	}
}

void	free_cmd(t_pi *pip)
{
	int i;
	int	j;

	i = 0;
	if (pip->cmd)
	{
		while (pip->cmd[i])
		{
			j = 0;
			while (pip->cmd[i][j])
			{
				free(pip->cmd[i][j]);
				j++;
			}
			free(pip->cmd[i]);
			i++;
		}
		free(pip->cmd);
	}
}

void	ft_end(t_pi *pip)
{
	int	i;

	i = 0;
	if (pip->fd_in > 0)
		close(pip->fd_in);
	if (pip->fd_out > 0)
		close(pip->fd_out);
	if (pip->arg)
	{
		while (pip->arg[i])
		{
			free(pip->arg[i]);
			i++;
		}
		free(pip->arg);
	}
	free_cmd(pip);
	free_pipe(pip);
	free(pip);
}