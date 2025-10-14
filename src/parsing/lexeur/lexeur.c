#include "minishell.h"

static int	find_meta_token(t_token *token)
{
	if (token->type == MORE || token->type == REDIRECT_A
		|| token->type == HERE_DOC || token->type == LESS
		|| token->type == PIPE)
		return (1);
	return (0);
}

int	verif_metachar_redir(t_shell *shell)
{
	t_token	*token;

	token = shell->token;
	if (token && token->type == PIPE)
		return (error_find_int(shell, META, 2, token->sentence));
	while (token)
	{
		if (find_meta_token(token))
		{
			if (!token->next)
				return (error_find_int(shell, META, 2, token->sentence));
			if (token->type != PIPE)
			{
				if (find_meta_token(token->next))
					return (error_find_int(shell, META, 2, token->sentence));
			}
			else
			{
				if (token->next->type == PIPE)
					return (error_find_int(shell, META, 2, token->sentence));
			}
		}
		token = token->next;
	}
	return (0);
}

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

int	lexeur(t_shell *shell)
{
	t_token	*temp;

	temp = shell->token;
	while (temp)
	{
		attribute(temp);
		temp = temp->next;
	}
	temp = shell->token;
	if (verif_metachar_redir(shell))
		return (1);
	return (0);
}
