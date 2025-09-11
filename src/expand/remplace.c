/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:28:00 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/11 13:28:08 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remplace(char **str_new, int j, char *var, int len_name)
{
	char	*pre;
	char	*post;
	char	*new;
	int		len_post;

	len_post = len_name + 1 + j;
	pre = ft_substr(*str_new, 0, j);
	if (!pre)
		return (1);
	post = ft_substr(*str_new, len_post, ft_strlen(*str_new) - len_post);
	if (!post)
	{
		free(pre);
		return (1);
	}
	new = ft_strjoin_var(3, pre, var, post);
	if (!new)
		return (1);
	free(pre);
	free(post);
	free(*str_new);
	*str_new = new;
	return (0);
}
