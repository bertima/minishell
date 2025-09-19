#include "minishell.h"

static void	attribute(t_token *token)
{
	if (!ft_strcmp(token->sentence, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(token->sentence, "<"))
		token->type = LESS;
	else if (!ft_strcmp(token->sentence, ">"))
		token->type = MORE;
	else if (!ft_strcmp(token->sentence, "<<"))
		token->type = HERE_DOC;
	else if (!ft_strcmp(token->sentence, ">>"))
		token->type = REDIRECT_A;
	else
		token->type = WORD;
}

void	lexeur(t_shell *shell)
{
	t_token	*temp;

	temp = shell->token;
	while (temp)
	{
		attribute(temp);
		temp = temp->next;
	}
}
