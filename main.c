/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:07:15 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/17 16:16:59 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	t_pi	*pip;
	int	i;
	int	g;

	i = 0;
	g = 2;
	if (ac < 5)
		return (printf("error arg"));
	if (!allow(ac, av))
		return (printf("permission denied\n"));
	pip = (t_pi *)malloc(sizeof(t_pi));
	if (!pip)
		return (1);
	if (!check_arg(ac, av))
		return (printf("this is empty\n"));
	if (!ft_init(pip, ac, av))
	{
		ft_end(pip);
		return (1);
	}
	// while (g > 0)
	// {
	// 	printf("g = %d\n", g);
	// 	printf("pip->cmd[%d] %s\n", i, pip->cmd[i][0]);
	// 	ft_exec(pip, pip->cmd[i]);
	// 	i++;

	// }
	ft_end(pip);
	return (0);
}