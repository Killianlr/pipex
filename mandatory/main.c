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

static int	set_fd(int ac, char **av, t_p *pip)
{ 
	pip->args = NULL;
	pip->cmd = NULL;
	pip->path = NULL;
	if (access(av[1], R_OK) == -1)
        return (msg_error("Error access file\n", pip));
	pip->infile = open(av[1], O_RDONLY);
	if (pip->infile < 0)
		msg_error("error open infile\n", pip);
	pip->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000664);
	if (pip->outfile < 0)
		msg_error("error open outfile\n", pip);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_p	pip;

	if (ac != 5 || !envp[0])
		return (msg_error("error, wrong number of arg or environnement\n", &pip));
	set_fd(ac, av, &pip);
	av[2] = ft_is_empty(av[2]);
	av[3] = ft_is_empty(av[3]);
	pip.path = ft_split(find_path(envp, &pip), ':');
	if (pipe(pip.fd) < 0)
		msg_error ("error pipe\n", &pip);
	pip.pid1 = fork();
	if (pip.pid1 < 0)
		msg_error("error fork\n", &pip);
	if (pip.pid1 == 0)
		first_cmd(pip, av, envp);
	pip.pid2 = fork();
	if (pip.pid2 < 0)
		msg_error("error fork\n", &pip);
	if (pip.pid2 == 0)
		second_cmd(pip, av, envp);
	close_pipes(&pip);
	waitpid(pip.pid1, NULL, 0);
	waitpid(pip.pid2, NULL, 0);
	free_main(&pip);
	return (0);
}
