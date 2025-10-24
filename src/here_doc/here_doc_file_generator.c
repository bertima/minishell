/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_file_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:33:34 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/24 10:33:35 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	insert_name(char **str, char *nbr, char *time)
{
	char	*temp;

	temp = ft_strjoin_var(3, ".temp_file", nbr, time);
	if (!temp)
		return (1);
	ft_free(&nbr);
	ft_free(&time);
	free(*str);
	*str = temp;
	return (0);
}

int	generator_of_file_name(char **str, char *nbr_count, char *nbr_sec)
{
	static int	count;
	long		sec;
	int			len;

	sec = time(NULL);
	count++;
	nbr_count = ft_itoa(count);
	if (!nbr_count)
		return (1);
	nbr_sec = ft_ltoa(sec);
	if (!nbr_sec)
		return (free(nbr_count), 1);
	len = ft_strlen(".file_temp") + ft_strlen(nbr_count) + 1;
	*str = malloc(sizeof(char) * (len + ft_strlen(nbr_sec)));
	if (!*str)
		return (free(nbr_count), free(nbr_sec), 1);
	if (insert_name(str, nbr_count, nbr_sec))
		return (1);
	return (0);
}

int	here_doc(t_shell *shell, t_cmd *temp_cmd)
{
	temp_cmd = shell->cmd;
	while (temp_cmd)
	{
		if (manage_delimiter_hd(temp_cmd->redir))
			return (1);
		if (creat_here_doc(shell, temp_cmd, NULL, 0))
			return (1);
		temp_cmd = temp_cmd->next;
	}
	return (0);
}
