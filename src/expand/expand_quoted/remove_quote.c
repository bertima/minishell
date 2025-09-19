#include "minishell.h"

static char	*free_quit(char **pre, char **inter, char **post)
{
	if (pre && *pre)
		free(*pre);
	if (inter && *inter)
		free(*inter);
	if (post && *post)
		free(*post);
	return (NULL);
}

static int	len_close_quote(char *str, int start)
{
	char	quote;
	int		len;

	quote = str[start];
	len = start + 1;
	while (str[len] && str[len] != quote)
		(len)++;
	return (len);
}

static char	*new_string(char *str, int start, int end)
{
	char	*pre;
	char	*inter;
	char	*post;
	char	*join;

	pre = ft_substr(str, 0, start);
	if (!pre)
		return (NULL);
	inter = ft_substr(str, start + 1, end - start - 1);
	if (!inter)
		return (free_quit(&pre, NULL, NULL));
	post = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	if (!post)
		return (free_quit(&pre, &inter, NULL));
	join = ft_strjoin_var(3, pre, inter, post);
	if (!join)
		return (free_quit(&pre, &inter, &post));
	free_quit(&pre, &inter, &post);
	return (join);
}

int	remove_quote(char **str, int *start)
{
	char	*temp;
	int		end;
	int		save;

	save = *start;
	end = len_close_quote(*str, *start);
	temp = new_string(*str, *start, end);
	if (!temp)
		return (1);
	free(*str);
	*str = temp;
	*start = save + (end - save - 1);
	if (*start < 0)
		*start = 0;
	return (0);
}
