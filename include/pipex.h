/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:47:22 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 11:52:30 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_p
{
	int		infile;
	int		outfile;
	int		fd[2];
	int		pid1;
	int		pid2;
	char	**path;
	char	**args;
	char	*cmd;
}t_p;

char	*find_path(char **envp, t_p *pip);
void	first_cmd(t_p pip, char **av, char **envp);
void	second_cmd(t_p pip, char **av, char **envp);
void	free_fork1(t_p *pip);
void	free_fork2(t_p *pip);
void	close_pipes(t_p *pip);
int		msg_error(char *str, t_p *pip);
void	free_main(t_p *pip);
void	child(t_p pip, char **av, char **envp);

#endif