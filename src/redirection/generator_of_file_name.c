#include "minishell.h"

static int	insert_name(char **str, char *nbr, char *time)
{
	char	*temp;

	temp = ft_strjoin_var(3, "temp_file", nbr, time);
	if (!temp)
		return (1);
	free(*str);
	*str = temp;
	return (0);
}

int	generator_of_file_name(char **str, char *nbr_count, char *nbr_sec)
{
	static int	count;
	pid_t		sec;
	int			len;

	sec = time(NULL);
	count++;
	nbr_count = ft_itoa(count);
	if (!nbr_count)
		return (1);
	nbr_sec = ft_itoa(sec);
	if (!nbr_sec)
		return (free(nbr_count), 1);
	len = ft_strlen("file_temp") + ft_strlen(nbr_count) + 1;
	*str = malloc(sizeof(char) * (len + ft_strlen(nbr_sec)));
	if (!*str)
		return (free(nbr_count), free(nbr_sec), 1);
	if (insert_name(str, nbr_count, nbr_sec))
		return (free(nbr_count), free(nbr_sec), 1);
	return (free(nbr_count), free(nbr_sec), 0);
}
