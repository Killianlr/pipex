/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:40:22 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/18 13:33:19 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int	set_str_cmd(t_pi *pip)
{
	int	i;
	int	j;

	i = 0;
	while (pip->arg[i])
		i++;
	pip->cmd = malloc(sizeof(char **) * (i + 1));
	if (!pip->cmd)
		return (0);
	i = 0;
	while (pip->arg[i])
	{
		pip->cmd[i] = ft_split(pip->arg[i], ' ');
		j = 0;
		// while (pip->cmd[i][j]) // A SUPPRIMER 
		// {
		// 	printf("pip->cmd[%d][%d] = %s\n", i, j, pip->cmd[i][j]);
		// 	j++;
		// }						// A SUPPRIMER
		i++;
	}
	pip->cmd[i] = NULL;
	return (1);
}

int	parse_arg(t_pi *pip, int ac, char **av)
{
	int	i;
	// int countemp;

	i = 0;
	// countemp = 1;
	(void)av;
	pip->arg = malloc(sizeof(char *) * (ac - 2));
	if (!pip->arg)
		return (0);
	while (ac - 3)
	{
		pip->arg[i] = malloc(sizeof(char) * (ft_strlen_space(av[2 + i]) + 1));
		if (!pip->arg[i])
			return (0);
		pip->arg[i] = remove_white_space(pip->arg[i], av[2 + i]);
		// printf("cmd%d -> %s\n", countemp, pip->arg[i]);
		i++;
		// countemp++;
		ac--;
	}
	pip->arg[i] = NULL;
	set_str_cmd(pip);
	return (1);
}

void	ft_exec(t_pi *pip)
{
	pip->pid = fork();
	if (!pip->pid)
	{
		if (pip->idx == 0)
			swap_dup2(pip->fd_in, pip->pipe[1]);
	}
}

int	ft_init(t_pi *pip, int ac, char **av)
{
	pip->fd_in = open(av[1], O_RDONLY);
	if (pip->fd_in == -1)
		return (0);
	pip->fd_out = open(av[ac - 1], O_WRONLY);
	if (pip->fd_out == -1)
		return (0);
	pip->path = "/bin/";
	parse_arg(pip, ac, av);
	ft_exec(pip);
	// printf("here");
	return (1);
}

int	allow(int ac, char **av)
{
	if (access(av[1], R_OK) == -1)
		return (0);
	if (access(av[ac - 1], W_OK) == -1)
		return (0);
	if (access(av[ac - 1], R_OK) == -1)
		return (0);
	return (1);
}