/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:03:38 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/05 11:11:52 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_redirect(t_command *command, t_token *token, int type)
{
	t_redir	*temp;
	t_redir	*new;

	new = calloc(1, sizeof(t_redir));
	if (!new)
		return (1);
	new->type = type;
	new->file = ft_strdup(token->next->sentence);
	if (!new)
	{
		free(new);
		return (1);
	}
	if (!command->redir)
		command->redir = new;
	else
	{
		temp = command->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

static void	here_doc_expand(t_redir *redir)
{
	t_redir	*temp;
	int		i;

	i = 0;
	temp = redir;
	while (temp->next)
		temp = temp->next;
	if (temp->type == HERE_DOC)
	{
		while(temp->file && temp->file[i])
		{
			if (temp->file[i] == '\'' || temp->file[i] == '\"')
			{	
				temp->hd_expand = 1;
				return ;
			}
			i++;
		}
	}
}

int	redirect(t_command *command, t_token **token)
{
	if (!(*token) || !(*token)->next)
		return (1);
	if (add_redirect(command, *token, (*token)->type))
		return (1);
	here_doc_expand(command->redir);
	*token = (*token)->next;
	return (0);
}
