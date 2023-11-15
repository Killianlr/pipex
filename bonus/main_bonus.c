/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:55:48 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 15:16:30 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	get_pipes(t_p *pip)
{
	int	i;

	i = 0;
	while (i < pip->cmd_nbr - 1)
	{
		if (pipe(pip->pipe + 2 * i) < 0)
			free_parent(pip);
		i++;
	}
}

void	files_in_out(int ac, char **av, t_p *pip)
{
	if (pip->here_doc)
	{
		get_here_doc(av[2], pip);
		pip->outfile = open(av[ac - 1], O_TRUNC | O_RDWR
				| O_CREAT | O_APPEND, 0000644);
		if (pip->outfile < 0)
			msg_error("error open outfile\n");
	}
	else
	{
		if (access(av[1], R_OK) == -1)
			msg_error("error access file\n");
		pip->infile = open(av[1], O_RDONLY);
		if (pip->infile < 0)
			msg_error("error open infile\n");
		pip->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (pip->outfile < 0)
			msg_error("error open outfile\n");
	}
}

int	av_count(char *av, t_p *pip)
{
	if (!ft_strncmp(av, "here_doc", 9))
	{
		pip->here_doc = 1;
		return (6);
	}
	else
	{
		pip->here_doc = 0;
		return (5);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_p	pip;

	if (ac < av_count(av[1], &pip) || !envp[0])
		return (msg_error("error input\n"));
	files_in_out(ac, av, &pip);
	pip.cmd_nbr = ac -3 -pip.here_doc;
	pip.pipe_nbr = 2 * (pip.cmd_nbr - 1);
	pip.pipe = malloc(sizeof(int) * pip.pipe_nbr);
	if (!pip.pipe)
		msg_error("error pipe\n");
	pip.path = ft_split(find_path(envp), ':');
	if (!pip.path)
		free_pipe(&pip);
	get_pipes(&pip);
	pip.idx = -1;
	while (++(pip.idx) < pip.cmd_nbr)
		child(pip, av, envp);
	close_pipes(&pip);
	waitpid(-1, NULL, 0);
	free_main(&pip);
	return (0);
}