#include "../include/pipex_bonus.h"

void    free_pipe(t_p *pip)
{
    close(pip->infile);
    close(pip->outfile);
    if (pip->here_doc)
        unlink(".heredoc_tmp");
    free(pip->pipe);
    write(2, "error envp\n", 12);
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