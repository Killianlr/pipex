/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:53:40 by kle-rest          #+#    #+#             */
/*   Updated: 2022/12/13 17:10:15 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_next(char *stash)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	next = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!next)
		return (NULL);
	j = 0;
	while (stash[i])
		next[j++] = stash[i++];
	next[j] = '\0';
	free(stash);
	return (next);
}

char	*ft_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (stash[0] == '\0')
		return (NULL);
	line = ft_calloc(sizeof(char), (ft_strlen(stash) + 1));
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *stash)
{
	char	*bufread;
	int		ret;

	ret = 1;
	bufread = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (ret != 0 && ft_checkline(stash) == 0)
	{
		ret = read(fd, bufread, BUFFER_SIZE);
		if (ret == -1)
		{
			free(bufread);
			return (NULL);
		}
		bufread[ret] = 0;
		stash = ft_strjoin(stash, bufread);
	}
	free(bufread);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_line(stash[fd]);
	stash[fd] = ft_next(stash[fd]);
	return (line);
}
