/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:28:02 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/04 11:38:50 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(t_command *command, t_token **token)
{
	t_token	*temp;

	temp = (*token)->next;
	if (!token || !*token || !(*token)->next)
		return (1);
	if ((*token)->type == MORE)
		command->outfile = temp->sentence;
	else if ((*token)->type == LESS)
		command->infile = temp->sentence;
	else if ((*token)->type == HERE_DOC)
	{
		command->infile = (*token)->next->sentence;
		command->here_doc = 1;
	}
	else if ((*token)->type == REDIRECT_A)
	{
		command->outfile = (*token)->sentence;
		command->append = 1;
	}
	*token = (*token)->next;
	return (0);
}

static int	compare(t_minishell *minishell, t_command **command, t_token **temp)
{
	if (!*command)
	{
		if (add_command(minishell, command))
			return (1);
		return (0);
	}
	else if ((*temp)->type == PIPE)
	{
		if (add_command(minishell, command))
			return (1);
	}
	else if ((*temp)->type != WORD)
	{
		if (redirect(*command, temp))
			return (1);
	}
	else
	{
		if (add_arg((*command), *temp, (*command)->nbr_arg))
			return (1);
	}
	*temp = (*temp)->next;
	return (0);
}

int	creat_command(t_minishell *minishell)
{
	t_command	*command;
	t_token		*temp;

	temp = minishell->token;
	command = NULL;
	while (temp)
	{
		if (compare(minishell, &command, &temp))
			return (return_err_int(minishell, "creat_command fail\n"));
	}
	return (0);
}
