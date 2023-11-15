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

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

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
	char	**path;
	char	**args;
	char	*cmd;	
}t_p;

void	crash_here_doc(void);
char	*find_path(char **envp);
void    free_pipe(t_p *pip);
void    close_pipes(t_p *pip);
void	free_child(t_p *pip);
void    free_parent(t_p *pip);
void	free_main(t_p *pip);
int		msg_error(char *str);
int		pi_strcmp(char *s1, char *s2, int n);

#endif