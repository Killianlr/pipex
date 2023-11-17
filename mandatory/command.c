/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:12:14 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 11:55:10 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_cmd(char **paths, char	**cmd, char **envp)
{
	char	*tmp;
	char	*command;

	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
	{
		if (access(cmd[0], 0) == 0)
			execve(cmd[0], cmd, envp);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_cmd(t_p pip, char **av, char **envp)
{
	dup2(pip.infile, 0);
	close(pip.infile);
	close(pip.fd[0]);
	dup2(pip.fd[1], 1);
	pip.cmd = NULL;
	pip.args = ft_split(av[2], ' ');
	pip.cmd = get_cmd(pip.path, pip.args, envp);
	if (!pip.cmd)
	{
		write(2, "command not found: ", 20);
		write(2, pip.args[0], ft_strlen(pip.args[0]));
		write(2, "\n", 1);
		free_fork1(&pip);
		exit(1);
	}
	execve(pip.cmd, pip.args, envp);
}

void	second_cmd(t_p pip, char **av, char **envp)
{
	dup2(pip.outfile, 1);
	close(pip.outfile);
	close(pip.fd[1]);
	dup2(pip.fd[0], 0);
	pip.cmd = NULL;
	pip.args = ft_split(av[3], ' ');
	pip.cmd = get_cmd(pip.path, pip.args, envp);
	if (!pip.cmd)
	{
		write(2, "command not found: ", 20);
		write(2, pip.args[0], ft_strlen(pip.args[0]));
		write(2, "\n", 1);
		free_fork2(&pip);
		exit(1);
	}
	execve(pip.cmd, pip.args, envp);
}
