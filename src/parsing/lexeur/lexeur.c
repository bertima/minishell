/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 09:35:44 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/03 09:35:57 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void attribute(t_token *token)
{
    if (!ft_strcmp(token->token, "|"))
        token->type = PIPE;
    else if (!ft_strcmp(token->token, "<"))
        token->type = LESS;
    else if (!ft_strcmp(token->token, ">"))
        token->type = MORE;
    else if (!ft_strcmp(token->token, "<<"))
        token->type = HERE_DOC;
    else if (!ft_strcmp(token->token, ">>"))
        token->type = REDIRECT_A;
    else
        token->type = WORD;
}

//permet de voir si type bien attribuer
/*static void lexer_test(t_minishell *minishell)
{
    t_token *temp;
    int i = 1;

    // Affiche chaque token et son contenu
    temp = minishell->token;
    while (temp)
    {
        printf("Token %d: \"%s\"\n", i, temp->token);
        printf("TYPE : %d\n", temp->type);
        i++;
        temp = temp->next;
    }
}*/

void    lexeur(t_minishell *minishell)
{
    t_token *temp;

    temp = minishell->token;
    while (temp)
    {
        attribute(temp);
        temp = temp->next;
    }
//    lexer_test(minishell);
}