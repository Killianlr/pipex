/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:55:48 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/15 14:58:47 by kle-rest         ###   ########.fr       */
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
		pip->outfile = open(av[ac - 1], O_RDWR
				| O_CREAT | O_APPEND, 0000644);
		if (pip->outfile < 0)
			msg_error("error open outfile\n", pip);
	}
	else
	{
		if (access(av[1], R_OK) == -1)
			msg_error("error access file\n", pip);
		pip->infile = open(av[1], O_RDONLY);
		if (pip->infile < 0)
			msg_error("error open infile\n", pip);
		pip->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (pip->outfile < 0)
			msg_error("error open outfile\n", pip);
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

void	check_args(int ac, char **av, t_p *pip)
{
	int	i;

	i = 2 + pip->here_doc;
	while (i < ac)
	{
		av[i] = ft_is_empty(av[i]);
		i++;
	}
	pip->path = NULL;
	pip->args = NULL;
	pip->cmd = NULL;
	pip->pipe = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_p	pip;

	if (ac < av_count(av[1], &pip) || !envp[0])
		return (write(2, "error input\n", 13));
	check_args(ac, av, &pip);
	files_in_out(ac, av, &pip);
	pip.cmd_nbr = ac - 3 - pip.here_doc;
	pip.pipe_nbr = 2 * (pip.cmd_nbr - 1);
	pip.pipe = malloc(sizeof(int) * pip.pipe_nbr);
	if (!pip.pipe)
		msg_error("error pipe\n", &pip);
	pip.path = ft_split(find_path(envp, &pip), ':');
	if (!pip.path)
		free_pipe(&pip);
	get_pipes(&pip);
	pip.idx = -1;
	while (++(pip.idx) < pip.cmd_nbr)
		child(pip, av, envp);
	close_pipes(&pip);
	free_main(&pip);
	waitpid(-1, NULL, 0);
	return (0);
}
