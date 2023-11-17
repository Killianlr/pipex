/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:49:01 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 11:51:43 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_is_empty(char *str)
{
	int	len;
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	if (len == 0)
		return ("empty");
	while (i < len)
	{
		if (str[i] > 32 && str[i] < 127)
			return (str);
		i++;
	}
	return ("empty");
}
