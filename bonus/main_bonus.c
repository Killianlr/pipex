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

int	ft_check_arg(t_p *pip, int ac, char **av)
{
	if (ac == 1)
	{
		free(pip);
		return (0);
	}
	if (!ft_strncmp(av[1], "here_doc", 9))
		pip->here_doc = 1;
	else
		pip->here_doc = 0;
	if (ac < 5 + pip->here_doc)
	{
		free(pip);
		return (0);
	}
	return (1);
}

int	ft_init(t_p *pip, int ac, char **av)
{
	if (pip->here_doc)
		here_doc(av[2], pip);
	else
	{
		pip->infile = open(av[1], O_RDONLY);
		if (pip->infile < 0)
		{
			free(pip);
			return (0);
		}
	}
	pip->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000664);
	if (pip->outfile < 0)
	{
		free(pip);
		return (0);
	}
	return (1);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	ft_fill_struct(t_p *pip, int ac)
{
	pip->cmd_nbr = ac - 3 - pip->here_doc;
	pip->pipe_nbr = 2 * (pip->cmd_nbr - 1);
	pip->pipe = malloc(sizeof(int) * pip->pipe_nbr);
	if (!pip->pipe)
	{
		free(pip);
		return (0);
	}
	return (1);
}

void	creat_pipes(t_p *pip)
{
	int	i;

	i = 0;
	while (i < pip->cmd_nbr - 1)
	{
		if (pipe(pip->pipe + 2 * i) < 0)
			ft_free_path(pip);
		i++;
	}
}

void	double_dup2(int	zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	close_pipes(t_p *pip)
{
	int	i;

	i = 0;
	while (i < pip->pipe_nbr)
	{
		close(pip->pipe[i]);
		i++;
	}
}

char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		path++;
	}
	printf("here\n");
	return (NULL);
}

void	ft_exec(t_p *pip, char **av, char **envp)
{
	pip->pid = fork();
	if (!pip->pid)
	{
		if (pip->idx == 0)
			double_dup2(pip->infile, pip->pipe[1]);
		else if (pip->idx == pip->cmd_nbr - 1)
			double_dup2(pip->pipe[2 * pip->idx - 2], pip->outfile);
		else
			double_dup2(pip->pipe[2 * pip->idx - 2], pip->pipe[2 * pip->idx + 1]);
		close_pipes(pip);
		pip->cmd_args = ft_split(av[2 + pip->here_doc + pip->idx], ' ');
		pip->cmd = get_cmd(pip->cmd_path, pip->cmd_args[0]);
		if (!pip->cmd)
		{
			msg_pipe(pip->cmd_args[0]);
			ft_free_args(pip);
			exit(1);
		}
		execve(pip->cmd, pip->cmd_args, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_p	*pip;

	pip = (t_p *)malloc(sizeof(t_p));
	if (!ft_check_arg(pip, ac, av))
		return (msg(ERR_INPUT));
	if (!ft_init(pip, ac, av))
		return (msg(ERR));
	pip->path = find_path(envp);
	pip->cmd_path = ft_split(pip->path, ':');
	if (!pip->cmd_path)
		ft_free(pip);
	if (!ft_fill_struct(pip, ac))
		return (msg(ERR_MALLOC));
	creat_pipes(pip);
	pip->idx = -1;
	while (++(pip->idx) < pip->cmd_nbr)
		ft_exec(pip, av, envp);
	close_pipes(pip);
	waitpid(-1, NULL, 0);
	ft_free_path(pip);
	return (0);
}