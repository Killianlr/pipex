/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:00:53 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/18 14:05:28 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipexM.h"

int		msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	msg_error(char *err)
{
	perror(err);
	exit (1);
}