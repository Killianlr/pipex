/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:20:31 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/19 15:57:45 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(t_p *pip)
{
	close(pip->infile);
	close(pip->outfile);
	if (pip->here_doc)
		unlink(".heredoc_tmp");
	free(pip);
	msg(ERR_MALLOC);
	exit(1);
}

void	ft_free_path(t_p *pip)
{
	int	i;

	i = 0;
	close(pip->infile);
	close(pip->outfile);
	if (pip->here_doc)
		unlink(".heredoc_tmp");
	while (pip->cmd_path[i])
	{
		free(pip->cmd_path[i]);
		i++;
	}
	free(pip->cmd_path);
	free(pip->pipe);
}

void	ft_free_args(t_p *pip)
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