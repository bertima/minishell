/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:10:08 by bertrmar          #+#    #+#             */
/*   Updated: 2025/07/21 10:10:22 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recup_in(char **av)
{
	char	*str;
	char	*word_stop;

	write (0, "> ", 2);
	str = get_next_line(0);
	word_stop = ft_strjoin(av[2], "\n");
	if (!word_stop)
		return (1);
	while (str)
	{
		if (ft_strcmp(str, word_stop) == 0)
		{
			free(str);
			free(word_stop);
			get_next_line(-1);
			return (0);
		}
		write (2, "> ", 2);
		ft_printf("%s", str);
		free(str);
		str = get_next_line(0);
	}
	free(word_stop);
	return (1);
}
