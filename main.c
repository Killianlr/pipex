/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:07:15 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/12 13:50:12 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	t_pi	*pip;

	// printf("ac = %d\n", ac);
	if (ac < 5)
		return (printf("error arg"));
	if (!allow(ac, av))
		return (printf("permission denied\n"));
	pip = (t_pi *)malloc(sizeof(t_pi));
	if (!pip)
		return (1);
	if (!check_arg(ac, av))
		return (printf("this is empty\n"));
	ft_init(pip, ac, av);
	ft_end(pip);
	return (0);
}