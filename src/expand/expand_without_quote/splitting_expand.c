/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:44:56 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/11 15:21:44 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	first_arg(char ***arg, char *str, int start, int len)
{
	*arg = calloc(2, sizeof(char *));
	if (!*arg)
		return (1);
	*arg[0] = ft_substr(str, start, len);
	if (!*arg[0])
	{
		free(arg[1]);
		return (1);
	}
	return (0);
}

static int	new_arg(char ***temp, char **arg, int len_tab)
{
	int	i;

	i = 0;
	*temp = ft_calloc(len_tab + 2, sizeof(char *));
	if (!*temp)
	{
		ft_free_split(arg);
		return (1);
	}
	while (arg[i])
	{
		*temp[i] = arg[i];
		i++;
	}
	*temp[i] = NULL;
	return (0);
}

static int	add_argument(char ***arg, char *str, int start, int len)
{
	int		len_tab;
	char	**temp;

	len_tab = ft_len_double_char(*arg);
	if (len_tab == 0)
	{
		if (first_arg(arg, str, start, len))
			return (1);
		return (0);
	}
	if (new_arg(&temp, *arg, len_tab))
		return (1);
	temp[len_tab] = ft_substr(str, start, len);
	if (!temp[len_tab])
	{
		ft_free_split(temp);
		ft_free_split(*arg);
		return (1);
	}
	temp[len_tab + 1] = NULL;
	ft_free_split(*arg);
	*arg = temp;
	return (0);
}

int	word_splitting(char ***arg, char *str)
{
	int		start;
	int		len;

	start = 0;
	len = 0;
	while (str[start])
	{
		while (str[start] && ft_isspace(str[start]))
			start++;
		if (!str[start])
			break ;
		while (str[start + len] && !ft_isspace(str[start + len]))
			len++;
		if (add_argument(arg, str, start, len))
			return (1);
		start += len;
		len = 0;
	}
	return (0);
}
