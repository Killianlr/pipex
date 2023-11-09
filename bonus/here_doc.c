/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:16:07 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 15:16:20 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int		ft_error(char *str)
{
	perror(str);
	exit(0);
}

void    here_doc(char *av, t_p *pip)
{
    int     file;
    char    *buf;

    file = open(".heredoc_tmp", O_CREAT | O_RDONLY | O_TRUNC, 000644);
    if (file < 0)
        msg_error(ERR_HEREDOC);
    while (1)
    {
        write(1, "heredoc> ", 9);
        buf = get_next_line(0, 0);
        if (!buf)
            ft_error(ERR_GNL);
        if(!ft_strncmp(av, buf, ft_strlen(av)))
            break ;
        write(file, buf, ft_strlen(buf));
        write(file, "\n", 1);
        free(buf);
    }
    get_next_line(0, 1);
    free(buf);
    close(file);
    pip->infile = open(".heredoc_tmp", O_RDONLY);
    if (pip->infile < 0)
    {
        unlink(".heredoc_tmp");
        msg_error(ERR_HEREDOC);
    }
}