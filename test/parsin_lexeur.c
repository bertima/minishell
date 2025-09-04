A mettre dans lexeur

static void lexer_test(t_minishell *minishell)
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
}
