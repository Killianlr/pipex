/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:40:22 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/10 16:59:08 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_init(t_pi *pip, int ac, char **av)
{
	pip->fd_in = open(av[1], O_RDONLY);
	if (pip->fd_in == -1)
		return (1);
	pip->fd_out = open(av[ac - 1], O_WRONLY);
	if (pip->fd_out == -1)
		return (1);
	printf("here");
	return (0);
}

int	allow(int ac, char **av)
{
	if (access(av[1], R_OK) != -1)
		return (1);
	if (access(av[ac - 1], W_OK) != -1)
		return (1);
	if (access(av[ac - 1], R_OK) != -1)
		return (1);
	return (0);
}