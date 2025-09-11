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
		printf(" file : %s", redir->file);
		printf(" : here_doc_expand : %d\n", redir->hd_expand);
		redir = redir->next;
	}
}

void	show_commands(t_command *command, int i, int cmd_index)
{
	t_redir	*redir;

	redir = NULL;
	while (command)
	{
		i = 0;
		printf("=== Command %d ===\n", cmd_index);
		if (command->arg && command->arg[0])
			printf("Name: %s\n", command->arg[0]);
		else
			printf("Name: (null)\n");
		if (command->arg)
		{
			while (command->arg[i])
			{
				printf("Args %d : %s\n", i, command->arg[i]);
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

void	show_lexeur(t_shell *shell)
{
	t_token	*temp;
	int		i;

	i = 1;
	temp = shell->token;
	while (temp)
	{
		printf("Token %d: %s\n", i, temp->sentence);
		printf("TYPE : %d\n", temp->type);
		i++;
		temp = temp->next;
	}
}

void	show_token(t_shell *shell)
{
	t_token	*temp;
	int		i;

	i = 1;
	temp = shell->token;
	while (shell->token)
	{
		temp = temp->next;
		printf("%s: token %d\n", shell->token->sentence, i);
		i++;
		shell->token = temp;
	}
}
