/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirect_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:27:48 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:27:49 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_redir_argument(t_redir *new, t_token *token)
{
	new->file = calloc(2, sizeof(char *));
	if (!new->file)
		return (1);
	new->file[0] = ft_strdup(token->next->sentence);
	if (!new->file[0])
		return (ft_free_split(new->file), 1);
	new->file[1] = NULL;
	return (0);
}

static int	add_redirect(t_cmd *cmd, t_token *token, int type)
{
	t_redir	*temp;
	t_redir	*new;

	new = calloc(1, sizeof(t_redir));
	if (!new)
		return (1);
	new->type = type;
	if (add_redir_argument(new, token))
	{
		if (new->file)
			ft_free_split(new->file);
		return (free(new), 1);
	}
	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		temp = cmd->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

int	manage_redirect_token(t_cmd *cmd, t_token **token)
{
	if (!(*token) || !(*token)->next)
		return (1);
	if (add_redirect(cmd, *token, (*token)->type))
		return (1);
	*token = (*token)->next;
	return (0);
}
