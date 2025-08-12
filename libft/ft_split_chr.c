/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_execpt_chr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:30:31 by bertrmar          #+#    #+#             */
/*   Updated: 2025/07/16 14:51:04 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*use this fonction if you want split with a special contion
exemple : awk '{print $2}' and you want keep "awk" and "{printf $2"}*/

#include "libft.h"

static int	char_ok(char c, char *str, t_split *data)
{
	int	i;

	i = 0;
	if (c == data->exept && data->wait == 0)
	{
		data->wait = 1;
		return (0);
	}
	else if (c == data->exept && data->wait == 1)
	{
		data->wait = 0;
		return (1);
	}
	while (str[i])
	{
		if (c == str[i] && data->wait == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	counter(char *str, char *c, t_split *data)
{
	int	i;
	int	count;
	int	wall;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	wall = 0;
	while (str[i])
	{
		if (char_ok(str[i], c, data) == 1 && wall == 1)
			wall = 0;
		if (char_ok(str[i], c, data) == 0 && wall == 0)
		{
			wall = 1;
			count++;
		}
		i++;
	}
	return (count);
}

void	search_arg(t_split *data, int *i, char *s, char *c)
{
	while (s[*i] && char_ok(s[*i], c, data) == 1)
		(*i)++;
	if (!s[*i])
		return ;
	if (s[*i] == data->exept)
	{
		(*i)++;
		data->start = *i;
		while (s[*i] && s[*i] != data->exept)
			(*i)++;
		data->end = *i;
		if (s[*i] == data->exept)
			(*i)++;
	}
	else
	{
		data->start = *i;
		while (char_ok(s[*i], c, data) == 0 && s[*i])
			(*i)++;
		data->end = *i;
	}
}

static char	**alloc_str(char **new, char *s, char *c, t_split *data)
{
	int	i;

	i = 0;
	while (s[i])
	{
		search_arg(data, &i, s, c);
		new[data->alloc] = ft_substr(s, data->start, data->end - data->start);
		if (!new[data->alloc])
		{
			ft_free_split(new);
			return (NULL);
		}
		data->alloc++;
	}
	return (new);
}

char	**ft_split_chr(char *s, char *c, char exept)
{
	t_split	data;
	int		count;

	if (!s)
		return (NULL);
	ft_memset(&data, 0, sizeof(t_split));
	data.exept = exept;
	data.new = NULL;
	count = counter(s, c, &data);
	data.new = (char **)malloc(sizeof(char *) * (count + 1));
	if (!data.new)
		return (NULL);
	data.wait = 0;
	if (!alloc_str(data.new, s, c, &data))
		return (NULL);
	data.new[count] = NULL;
	return (data.new);
}
