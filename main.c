/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:07:15 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/18 13:29:37 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	t_pi	*pip;

	if (ac < 5)
		return (printf("error arg"));
	if (!allow(ac, av))
		return (printf("permission denied\n"));
	pip = (t_pi *)malloc(sizeof(t_pi));
	if (!pip)
		return (1);
	if (!check_arg(ac, av))
		return (printf("this is empty\n"));
	pip->cmd_nmbr = ac - 3;
	pip->idx = -1;
	pip->pipe = malloc(sizeof(int) * (pip->idx * 2));
	if (!pip->pipe)
	{
		free(pip);		
		return (1);
	}
	if (!ft_init(pip, ac, av))
	{
		ft_end(pip);
		return (1);
	}
	ft_end(pip);
	return (0);
}