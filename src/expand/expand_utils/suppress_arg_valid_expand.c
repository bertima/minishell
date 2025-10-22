/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppress_arg_valid_expand.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:31:04 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:31:06 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	suppress_arg(char ***arg, int *i)
{
	char	**temp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	temp = calloc(ft_len_array(*arg), sizeof(char *));
	if (!temp)
		return (1);
	while ((*arg)[j])
	{
		if (j == *i)
			ft_free(&(*arg)[j]);
		else
			temp[k++] = (*arg)[j];
		j++;
	}
	temp[k] = NULL;
	(*i)--;
	free(*arg);
	*arg = temp;
	return (0);
}

int	ft_valid_expand(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}
