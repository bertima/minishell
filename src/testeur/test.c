/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:54:02 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/08 14:04:12 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_redir(t_command *command, t_redir *redir)
{
	redir = command->redir;
	while (redir)
	{
		printf("Redirection: ");
		if (redir->type == LESS)
			printf("<");
		else if (redir->type == MORE)
			printf(">");
		else if (redir->type == REDIRECT_A)
			printf(">>");
		else if (redir->type == HERE_DOC)
			printf("<<");
		printf(" file : %s\n", redir->file);
		redir = redir->next;
	}
}

void	show_commands(t_command *command, int i, int cmd_index)
{
	t_redir	*redir;

	redir = NULL;
	while (command)
	{
		printf("=== Command %d ===\n", cmd_index);
		if (command->arg && command->arg[0])
			printf("Name: %s\n", command->arg[0]);
		else
			printf("Name: (null)\n");
		if (command->arg)
		{
			printf("Args:");
			while (command->arg[i])
			{
				printf(" %s", command->arg[i]);
				i++;
			}
			printf("\n");
		}
		show_redir(command, redir);
		printf("\n");
		command = command->next;
		cmd_index++;
	}
}

void	lexer_test(t_minishell *minishell)
{
	t_token	*temp;
	int		i;

	i = 1;
	temp = minishell->token;
	while (temp)
	{
		printf("Token %d: \"%s\"\n", i, temp->sentence);
		printf("TYPE : %d\n", temp->type);
		i++;
		temp = temp->next;
	}
}

void	test_token(t_minishell *minishell)
{
	t_token	*temp;
	int		i;

	i = 1;
	temp = minishell->token;
	while (minishell->token)
	{
		temp = temp->next;
		printf("%s: token %d\n", minishell->token->sentence, i);
		if (minishell->token->sentence)
			free(minishell->token->sentence);
		if (minishell->token)
			free(minishell->token);
		i++;
		minishell->token = temp;
	}
}
