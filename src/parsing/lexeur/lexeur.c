/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 09:35:44 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/04 10:07:12 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	lexeur(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->token;
	while (temp)
	{
		attribute(temp);
		temp = temp->next;
	}
}
