#include "libft.h"

char    *ft_is_empty(char *str)
{
    int len;
    int i;

    if (!str)
        return(NULL);
    i = 0;
    len = ft_strlen(str);
    if (len == 0)
        return ("empty");
    while (i < len)
    {
        if (str[i] > 32 && str[i] < 127)
            return (str);
        i++;
    }
    return ("empty");
}
