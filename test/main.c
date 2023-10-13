/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:04:59 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/13 14:46:22 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

// int main()
// {
//     int fd[2];
//     pid_t pid;
//     char buffer[13];

//     if (pipe(fd) == -1)
//     {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid == 0)
//     {
//         close(fd[0]); // close the read end of the pipe
//         write(fd[1], "Hello parent!", 13);
//         close(fd[1]); // close the write end of the pipe
//         exit(EXIT_SUCCESS);
//     }
//     else
//     {
// 		printf("parent\n");
//         close(fd[1]); // close the write end of the pipe
//         read(fd[0], buffer, 13);
//         close(fd[0]); // close the read end of the pipe
//         printf("Message from child: '%s'\n", buffer);
//         exit(EXIT_SUCCESS);
//     }
// 	printf("ici\n");
// }

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*s12;
	int	len;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s12 = malloc(sizeof(char) * (len + 1));
	if (!s12)
		return (0);
	while (i < len)
	{
		if (i < ft_strlen(s1))
			s12[i] = s1[i];
		else
			s12[i] = s2[j++];
		i++;
	}
	s12[i] = 0;
	return (s12);
}

int	main()
{
	char	*arg[3];
	char	*str = "/bin/";

	arg[0] = "ls";
    arg[1] = "-l";
    arg[2] = NULL;
	execve(ft_strjoin(str, arg[0]), arg, NULL);
	return (0);
}