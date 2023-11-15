#include "../include/pipex_bonus.h"

int	msg_error(char *str)
{
	perror(str);
	exit (1);
}

int	pi_strcmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	if (n != (int)ft_strlen(s2) - 1)
		return (1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	crash_here_doc(void)
{
	unlink(".heredoc_tmp");
	msg_error("error here_doc\n");
}

static int	find_max_int_tab(char **env)
{
	int		r;

	r = 0;
	while (env[r])
		r++;
	return (r);
}

static char	*find_path_2(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*find_path(char **envp)
{
	int	r;
	int	max;

	r = 0;
	max = find_max_int_tab(envp);
	while (ft_strncmp("PATH", envp[r], 4) && r < max)
		r++;
	if (r == max)
		msg_error("error path\n");
	else
		return (find_path_2(envp));
	return (NULL);
}

void    free_pipe(t_p *pip)
{
    close(pip->infile);
    close(pip->outfile);
    if (pip->here_doc)
        unlink(".heredoc_tmp");
    free(pip->pipe);
    msg_error("error envp\n");
    exit(1);
}

void    close_pipes(t_p *pip)
{
    int i;

    i = 0;
    while (i < pip->pipe_nbr)
    {
        close(pip->pipe[i]);
        i++;
    }
}

void	free_child(t_p *pip)
{
	int	i;

	i = 0;
	while (pip->args && pip->args[i])
	{
		free(pip->args[i]);
		i++;
	}
	if (pip->args)
		free(pip->args);
	i = 0;
	while (pip->path && pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	if (pip->path)
		free(pip->path);
    if (pip->cmd)
        free(pip->cmd);
    if (pip->pipe)
        free(pip->pipe);
}

void    free_parent(t_p *pip)
{
    int i;

    i = 0;
    close(pip->infile);
	close(pip->outfile);
    if (pip->here_doc)
        unlink(".heredoc_tmp");
    while (pip->args && pip->args[i])
	{
		free(pip->args[i]);
		i++;
	}
	if (pip->args)
		free(pip->args);
    if (pip->pipe)
        free(pip->pipe);
}

void	free_main(t_p *pip)
{
	int	i;

	i = 0;
    close(pip->infile);
	close(pip->outfile);
	if (pip->here_doc)
        unlink(".heredoc_tmp");
	while (pip->path && pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	if (pip->path)
		free(pip->path);
    if(pip->pipe)
        free(pip->pipe);
}