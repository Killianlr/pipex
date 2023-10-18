/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexM.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:47:22 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/18 15:21:17 by kle-rest         ###   ########.fr       */
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

typedef struct s_p
{
	int	infile;
	int	outfile;
	int	tube[2];
	int	pid1;
	int	pid2;
	char	*path;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;	
}t_p;

void	first_cmd(t_p *pip, char **av, char **envp);
void	second_cmd(t_p *pip, char **av, char **envp);
void	parent_free(t_p *pip);
void	child_free(t_p *pip);
void	msg_error(char *err);
int		msg(char *err);

#endif