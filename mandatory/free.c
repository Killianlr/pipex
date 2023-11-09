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

void	parent_free(t_p *pip)
{
	int	i;

	i = 0;
	close(pip->infile);
	close(pip->outfile);
	while (pip->cmd_path[i])
	{
		free(pip->cmd_path[i]);
		i++;
	}
	free(pip->cmd_path);
}

void	child_free(t_p *pip)
{
	int	i;

	i = 0;
	while (pip->cmd_args[i])
	{
		free(pip->cmd_args[i]);
		i++;
	}
	free(pip->cmd_args);
	free(pip->cmd);
}