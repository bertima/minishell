#include "minishell.h"

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
		return (free(pre), NULL);
	post = ft_substr(str, end + 1, ft_strlen(str) - (end + 1));
	if (!post)
		return (free(pre), free(inter), NULL);
	join = ft_strjoin_var(3, pre, inter, post);
	if (!join)
		return (free(pre), free(inter), free(post), NULL);
	return (free(pre), free(inter), free(post), join);
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

char	*search_name(char *str, int start)
{
	int		len;
	char	*name;

	len = 0;
	while (ft_isalnum(str[start + len]))
		len++;
	if (len == 0)
		return (NULL);
	name = ft_substr(str, start, len);
	if (!name)
		return (NULL);
	return (name);
}
