#include "minishell.h"

static void	show_redir(t_cmd *cmd, t_redir *redir)
{
	int	i;

	i = 0;
	redir = cmd->redir;
	while (redir)
	{
		i = 0;
		printf("Redirection: ");
		if (redir->type == LESS)
			printf("<");
		else if (redir->type == MORE)
			printf(">");
		else if (redir->type == REDIRECT_A)
			printf(">>");
		else if (redir->type == HERE_DOC)
			printf("<<");
		printf(" : here_doc_expand : %d\n", redir->hd_expand);
		while (redir->file[i])
		{
			printf("file : %d, %s\n", i, redir->file[i]);
			i++;
		}
		redir = redir->next;
	}
}

void	show_commands(t_cmd *cmd, int i, int cmd_index)
{
	t_redir	*redir;

	redir = NULL;
	while (cmd)
	{
		i = 0;
		printf("=== Command %d ===\n", cmd_index);
		if (cmd->arg && cmd->arg[0])
			printf("Name: %s\n", cmd->arg[0]);
		else
			printf("Name: (null)\n");
		if (cmd->arg)
		{
			while (cmd->arg[i])
			{
				printf("Args %d : %s\n", i, cmd->arg[i]);
				i++;
			}
			printf("\n");
		}
		show_redir(cmd, redir);
		printf("\n");
		cmd = cmd->next;
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
