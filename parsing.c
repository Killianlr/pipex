/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:25:30 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/11 15:34:47 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_arg(int ac, char **av)
{
	int	i;
	int	c;

	i = 2;
	while (av[i])
	{
		c = 0;
		while (av[i][c] && i != ac - 1)
		{
			if (av[i][c] > 32 && av[i][c] < 127)
				return (1);
			c++;
		}
		i++;
	}
	return (0);
}

int	ft_strlen_space(char *str)
{
	int i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] >= 7 && str[i] <= 13) || (str[i] == ' ' && str[i + 1] == ' '))
			i++;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*remove_white_space(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str2[i] == ' ')
		i++;
	while (str2[i])
	{
		if ((str2[i] >= 7 && str2[i] <= 13) || (str2[i] == ' ' && str2[i + 1] == ' '))
			i++;
		else
		{
			// printf("str1[%d] = %c\n", j, str1[j]);
			str1[j] = str2[i];
			j++;
			i++;
		}
	}
	str1[j] = '\0';
	return (str1);
}