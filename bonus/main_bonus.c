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

void	set_fd(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	child(t_p pip, char **av, char **envp)
{
	pip.pid = fork();
	if (!pip.pid)
	{
		if (pip.idx == 0)
			set_fd(pip.infile, pip.pipe[1]);
		else if (pip.idx == pip.cmd_nbr - 1)
			set_fd(pip.pipe[2 * pip.idx - 2], pip.outfile);
		else
			set_fd(pip.pipe[2 * pip.idx - 2], pip.pipe[2 * pip.idx + 1]);
		close_pipes(&pip);
		pip.args = ft_split(av[2 + pip.idx + pip.here_doc], ' ');
		pip.cmd = get_cmd(pip.path, pip.args, envp);
		if(!pip.cmd)
		{
			write(2, "command not found: ", 20);
			write(2, pip.args[0], ft_strlen(pip.args[0]));
			write(2, "\n", 1);
			free_child(&pip);
			exit(1);
		}
		execve(pip.cmd, pip.args, envp);
	}	
}

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

void	get_here_doc(char *av, t_p *pip)
{
	int		doc;
	char	*buf;

	doc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (doc < 0)
		msg_error("error here_doc\n");
	while (1)
	{
		write(1, "heredoc> ", 10);
		buf = get_next_line(0, 0);
		if(!buf)
			msg_error("error get_next_line\n");
		if (!pi_strcmp(av, buf, ft_strlen(av)))
			break ;
		write(doc, buf, ft_strlen(buf));
		write(doc, "\n", 1);
		free(buf);
	}
	get_next_line(0, 1);
	free(buf);
	close(doc);
	pip->infile = open(".heredoc_tmp", O_RDONLY);
	if (pip->infile < 0)
		crash_here_doc();
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