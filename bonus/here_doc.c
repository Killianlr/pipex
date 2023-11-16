#include "../include/pipex_bonus.h"

void	crash_here_doc(t_p *pip)
{
	unlink(".heredoc_tmp");
	msg_error("error here_doc\n", pip);
}

void	get_here_doc(char *av, t_p *pip)
{
	int		doc;
	char	*buf;

	doc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (doc < 0)
		msg_error("error here_doc\n", pip);
	while (1)
	{
		write(1, "heredoc> ", 10);
		buf = get_next_line(0, 0);
		if(!buf)
			msg_error("error get_next_line\n", pip);
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
		crash_here_doc(pip);
}