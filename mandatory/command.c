/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:12:14 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 15:14:56 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_cmd(char **paths, char	*cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_cmd(t_p *pip, char **av, char **envp)
{
	dup2(pip->tube[1], 1);
	close(pip->tube[0]);
	dup2(pip->infile, 0);
	pip->cmd_args = ft_split(av[2], ' ');
	pip->cmd = get_cmd(pip->cmd_path, pip->cmd_args[0]);
	if(!pip->cmd)
	{
		child_free(pip);
		msg(ERR_CMD);
		exit(1);
	}
	execve(pip->cmd, pip->cmd_args, envp);
}

void	second_cmd(t_p *pip, char **av, char **envp)
{
	dup2(pip->tube[0], 0);
	close(pip->tube[1]);
	dup2(pip->outfile, 1);
	pip->cmd_args = ft_split(av[3], ' ');
	pip->cmd = get_cmd(pip->cmd_path, pip->cmd_args[0]);
	if(!pip->cmd)
	{
		child_free(pip);
		msg(ERR_CMD);
		exit(1);
	}
	execve(pip->cmd, pip->cmd_args, envp);
}