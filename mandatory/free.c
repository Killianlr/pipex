/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:47:02 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 15:15:24 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_main(t_p *pip)
{
	int	i;

	i = 0;
	while (pip->path && pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	if (pip->path)
		free(pip->path);
}

void	free_fork2(t_p *pip)
{
	int	i;

	i = 0;
	close(pip->infile);
	close(pip->outfile);
	while (pip->args && pip->args[i])
	{
		free(pip->args[i]);
		i++;
	}
	i = 0;
	while (pip->path && pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	if (pip->path)
		free(pip->path);
	if (pip->args)
		free(pip->args);
	if (pip->cmd)
		free(pip->cmd);
}

void	free_fork1(t_p *pip)
{
	int	i;

	i = 0;
	while (pip->args && pip->args[i])
	{
		free(pip->args[i]);
		i++;
	}
	i = 0;
	while (pip->path && pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	if (pip->path)
		free(pip->path);
	if (pip->args)
		free(pip->args);
	if (pip->cmd)
		free(pip->cmd);

}

int	msg_error(char *str, t_p *pip)
{
	int	i;

	write(2, str, ft_strlen(str));
	i = 0;
	while (pip->args && pip->args[i])
	{
		free(pip->args[i]);
		i++;
	}
	while (pip->path && pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	if (pip->path)
		free(pip->path);
	if (pip->args)
		free(pip->args);
	if (pip->cmd)
		free(pip->cmd);
	exit (1);
}
