/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:48:59 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/09 11:20:07 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*new_string(char *str, int start, int end)
{
	char	*inter;
	char	*post;
	char	*pre;
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

static int	single_quote(t_command *command, int *start, int i)
{
	char	*new;
	int		end;
	char	*str;

	str = command->arg[i];
	end = *start + 1;
	while (str[end] != '\'')
		end++;
	new = new_string(str, *start, end);
	if (!new)
		return (1);
	free(command->arg[i]);
	command->arg[i] = new;
	*start = end - 2;
	return (0);
}

static int	double_quote(t_shell *shell, t_command *command, int *start, int i)
{
	int		end;
	int		result;
	char	*name;
	char	*new;

	end = *start + 1;
	while (command->arg[i][end] != '\"')
	{
		if (command->arg[i][end] == '$')
		{
			name = search_name(command->arg[i], end + 1);
			if (name)
			{
				result = var_exist(shell, &command->arg[i], end, &name);
				if (result == 1)
					return (1);
				else if (result == 2)
					continue ;
			}
		}
		end++;
	}
	new = new_string(command->arg[i], *start, end);
	if (!new)
		return (1);
	free(command->arg[i]);
	command->arg[i] = new;
	*start = end - 2;
	return (0);
}

int	remove_quote(t_shell *shell, t_command *command, int i, int *start)
{
	char	*str;

	str = command->arg[i];
	if (str[*start] == '\'')
	{
		if (single_quote(command, start, i))
			return (1);
	}
	else
	{
		if (double_quote(shell, command, start, i))
			return (1);
	}
	return (0);
}
