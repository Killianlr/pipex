/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:04:59 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/18 11:54:51 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

// // int main()
// // {
// //     int fd[2];
// //     pid_t pid;
// //     char buffer[13];

// //     if (pipe(fd) == -1)
// //     {
// //         perror("pipe");
// //         exit(EXIT_FAILURE);
// //     }
// //     pid = fork();
// //     if (pid == -1)
// //     {
// //         perror("fork");
// //         exit(EXIT_FAILURE);
// //     }

// //     if (pid == 0)
// //     {
// //         close(fd[0]); // close the read end of the pipe
// //         write(fd[1], "Hello parent!", 13);
// //         close(fd[1]); // close the write end of the pipe
// //         exit(EXIT_SUCCESS);
// //     }
// //     else
// //     {
// // 		printf("parent\n");
// //         close(fd[1]); // close the write end of the pipe
// //         read(fd[0], buffer, 13);
// //         close(fd[0]); // close the read end of the pipe
// //         printf("Message from child: '%s'\n", buffer);
// //         exit(EXIT_SUCCESS);
// //     }
// // 	printf("ici\n");
// // }

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int	i;
// 	int	j;
// 	char	*s12;
// 	int	len;

// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	s12 = malloc(sizeof(char) * (len + 1));
// 	if (!s12)
// 		return (0);
// 	while (i < len)
// 	{
// 		if (i < ft_strlen(s1))
// 			s12[i] = s1[i];
// 		else
// 			s12[i] = s2[j++];
// 		i++;
// 	}
// 	s12[i] = 0;
// 	return (s12);
// }

// int	main()
// {
// 	char	*arg[3];
// 	char	*str = "/bin/";

// 	arg[0] = "ls";
//     arg[1] = "-l";
//     arg[2] = NULL;
// 	execve(ft_strjoin(str, arg[0]), arg, NULL);
// 	return (0);
// }

static int	ft_countword(const char *s, char c)
{
	int	count;
	int	i;
	int	word;

	count = 0;
	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c)
			word = 0;
		if (word == 0 && s[i] != c)
		{
			count++;
			word = 1;
		}
		i++;
	}
	return (count);
}

static int	ft_sizeword(const char *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] && s[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

static char	*ft_stricpy(char *dest, const char *src, char c, int i)
{
	int	j;

	j = 0;
	while (src[i] && src[i] != c)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static char	**ft_fill_tab(char **tab, const char *s, char c)
{
	int	r;
	int	i;
	int	w_len;

	r = 0;
	i = 0;
	while (r < ft_countword(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		w_len = ft_sizeword(s, c, i);
		tab[r] = malloc(sizeof(char) * (w_len + 1));
		if (!tab[r])
			return (NULL);
		tab[r] = ft_stricpy(tab[r], s, c, i);
		i += w_len;
		r++;
	}
	tab[r] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!tab)
		return (NULL);
	tab = ft_fill_tab(tab, s, c);
	return (tab);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]) && (i < (n - 1)))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int main(int argc, char *argv[], char *envp[])
{
	char	**cmd_path;
	char	*path;
	int	i = 0;

	path = find_path(envp);
	cmd_path = ft_split(path, ':');
	while (cmd_path[i])
		printf("%s\n", cmd_path[i++]);
    // // while(*envp)
    //     printf("%s\n",envp[30]);
}