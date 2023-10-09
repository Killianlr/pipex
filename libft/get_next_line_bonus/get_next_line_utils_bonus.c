/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:01:51 by kle-rest          #+#    #+#             */
/*   Updated: 2022/12/11 17:35:36 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_checkline(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc(int nmemb, int size)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb > 4294967295 / size)
		return (0);
	str = malloc(size * nmemb);
	if (!str)
		return (NULL);
	while (i < size * nmemb)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*len;

	i = -1;
	j = 0;
	if (!s1)
		s1 = ft_calloc(sizeof(char), 1);
	if (!s1 || !s2)
		return (NULL);
	len = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!len)
		return (NULL);
	while (s1[++i])
		len[i] = s1[i];
	while (s2[j])
		len[i++] = s2[j++];
	len[i] = '\0';
	free(s1);
	return (len);
}
