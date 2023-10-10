/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:07:15 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/10 16:57:26 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	t_pi	*pip;

	if (ac < 5)
		return (printf("error arg"));
	if (allow(ac, av) == 1)
		return (printf("permission denied\n"));
	pip = (t_pi *)malloc(sizeof(t_pi));
	if (!pip)
		return (1);
	ft_init(pip, ac, av);
	return (0);
}