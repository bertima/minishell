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

/*static char	*free_quit(char **pre, char **inter, char **post)
{
	if (pre && *pre)
		free(*pre);
	if (inter && *inter)
		free(*inter);
	if (post && *post)
		free(*post);
	return (NULL);
}

static char	*prepa(char *str, int end, int start)
{
	char	*inter;
	char	*post;
	char	*pre;
	char	*join;

	pre = ft_substr(str, 0, start);
	if (!pre)
		return (NULL);
	inter = ft_substr(str, start + 1 , end - start - 1);
	if (!inter)
		return (free_quit(&pre, NULL, NULL));
	post = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	if (!post)
		return (free_quit(&pre, &inter, NULL));
	join = ft_strjoin_var(3, pre, inter, post);
	if (!join)
		return (free_quit(&pre, &inter, &post));
	free(pre);
	free(inter);
	free(post);
	return (join);
}

static int	delete_quote(char **str, int start, int end)
{
	char	*new;

	new = prepa(*str, start, end);
	if (!new)
		return (1);
	free(*str);
	*str = new;
	return (0);
	
}

static int	search_end(t_command *command, int i, int *end, char c)
{
	int	start;
	
	start = *end;
	*end += 1;
	while (command->arg[i][*end] && command->arg[i][*end] != c)
		(*end)++;
	if (!command->arg[i][*end])
		return (1);
	if (delete_quote(&command->arg[i], start, *end))
		return (1);
	*end = start;
	return (0);
}*/

int	remove_quote(t_command *command, int i, int j)
{
	t_command	*temp;

	temp = command;
	while (temp)
	{
		i = 0;
		while (temp->arg && temp->arg[i])
		{
			j = 0;
			while (temp->arg[i][j])
			{
//				if (temp->arg[i][j] == '\'' || temp->arg[i][j] == '\"')
//				{
//					if (search_end(temp, i, &j, temp->arg[i][j]))
//						return (1);
//				}
				j++;
			}
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
