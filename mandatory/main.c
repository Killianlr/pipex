/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:57:07 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 15:15:29 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*find_path(char	**envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_p *pip)
{
	close(pip->tube[0]);
	close(pip->tube[1]);
}

int	main(int ac, char **av, char **envp)
{
	t_p	*pip;

	if (ac != 5)
		return (msg(ERR_INPUT));
	pip = (t_p *)malloc(sizeof(t_p));
	pip->infile = open(av[1], O_RDONLY);
	if (pip->infile < 0)
		msg_error(ERR_INFILE);
	pip->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000664);
	if (pip->outfile < 0)
		msg_error(ERR_OUTFILE);
	pip->path = find_path(envp);
	pip->cmd_path = ft_split(pip->path, ':');
	if (pipe(pip->tube) < 0)
		msg_error (ERR_PIPE);
	pip->pid1 = fork();
	if (pip->pid1 == 0)
		first_cmd(pip, av, envp);
	pip->pid2 = fork();
	if (pip->pid2 == 0)
		second_cmd(pip, av, envp);
	close_pipes(pip);
	waitpid(pip->pid1, NULL, 0);
	waitpid(pip->pid2, NULL, 0);
	parent_free(pip);
	free(pip);
	return (0);
}