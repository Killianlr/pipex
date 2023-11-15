/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:00:53 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 15:15:19 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	find_max_int_tab(char **env)
{
	int		r;

	r = 0;
	while (env[r])
		r++;
	return (r);
}

static char	*find_path_2(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*find_path(char **envp)
{
	int	r;
	int	max;

	r = 0;
	max = find_max_int_tab(envp);
	while (ft_strncmp("PATH", envp[r], 4) && r < max)
		r++;
	if (r == max)
		msg_error("error path\n");
	else
		return (find_path_2(envp));
	return (NULL);
}

void	close_pipes(t_p *pip)
{
	close(pip->fd[0]);
	close(pip->fd[1]);
}