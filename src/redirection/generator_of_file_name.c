#include "minishell.h"

static int  insert_name(char **str, char *nbr, char *pid)
{
    char    *temp;

    temp = ft_strjoin_var(3, "temp_file", nbr, pid);
    if (!temp)
        return (1);
    free(*str);
    *str = temp;
    return (0);
}

int  generator_of_file_name(char **str, char *nbr_count, char *nbr_pid)
{
    static int  count;
    pid_t       pid;
    int         len;

    pid = getpid();
    if (pid < 0)
        return (1);
    count++;
    nbr_count = ft_itoa(count);
    if (!nbr_count)
        return (1);
    nbr_pid = ft_itoa(pid);
    if (!nbr_pid)
        return (free(nbr_count), 1);
    len = ft_strlen("file_temp") + pid + ft_strlen(nbr_count) + 1;
    *str = malloc(sizeof(char) * (len + ft_strlen(nbr_pid)));
    if (!*str)
        return (free(nbr_count), free(nbr_pid), 1);
    if (insert_name(str, nbr_count, nbr_count))
        return (free(nbr_count), free(nbr_pid), 1);
    return (free(nbr_count), free(nbr_pid),  0);
}
