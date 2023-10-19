/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:47:22 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/19 15:57:41 by kle-rest         ###   ########.fr       */
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
# include <sys/wait.h>

# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_CMD "Commande not found\n"
# define ERR_PIPE "pipe"
# define ERR "error"
# define ERR_MALLOC "malloc failed"

typedef struct s_p
{
	int	infile;
	int	outfile;
	int		here_doc;
	int		cmd_nbr;
	int		pipe_nbr;
	int		idx;
	int		pid;
	int		*pipe;
	char	*path;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;	
}t_p;

void	msg_error(char *err);
int		msg(char *err);
void	msg_pipe(char *arg);
void	ft_free(t_p *pip);
void	ft_free_path(t_p *pip);
void	ft_free_args(t_p *pip);

#endif