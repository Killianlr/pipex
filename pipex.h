/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:13:35 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/11 15:27:17 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

typedef	struct s_pi
{
	int	fd_in;
	int	fd_out;
	char	**arg;
	char	***cmd;
}t_pi;

int		ft_init(t_pi *pip, int ac, char **av);
int		allow(int ac, char **av);
int		check_arg(int ac, char **av);
int		ft_strlen_space(char *str);
char	*remove_white_space(char *str1, char *str2);

#endif