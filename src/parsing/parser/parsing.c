/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:40:34 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/28 16:14:48 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(t_command *current, t_token *token)
{
	t_token *temp;

	temp = token->next;
	if (!temp || !temp->token || temp->type != WORD)
			return (1);
	if (temp->type == MORE)
		current->outfile = temp->token;
	else if (temp->type == LESS)
		current->infile = temp->token;
	else if (temp->type == HERE_DOC)
	{
		current->infile = temp->token;
		current->here_doc = 1;
	}
	else if (temp->type == REDIRECT_A)
	{
		current->outfile = temp->token;
		current->append = 1;
	}
	return (0);
}

int	parsing(t_minishell *minishell)
{
	if (tokening(minishell))
		return (return_err_int(minishell, "Token"));
	lexeur(minishell);
	if (creat_command(minishell))
		return (return_err_int(minishell, "creat"));
	//voir si les commande sont bien creer
	t_command *temp = minishell->command;
	int i = 1;
	while (temp)
	{
		printf("Command %d : name %s\n", i, temp->arg[0]->token);
		printf("info : infile %s, outilfile %s, append %d, here_doc %d\n", temp->infile, temp->outfile, temp->append, temp->here_doc);
		int j = 1;
		while (temp->arg[j])
		{
			printf("word %d : %s", j, temp->arg[j]->token);
			j++;
		}
		i++;
		temp = temp->next;
	}
	return (0);
}
