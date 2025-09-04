A mettre dans creat_token tokening

static void	test_token(t_minishell *minishell)
{
	t_token *temp = minishell->token;
	int i = 1;
	while (minishell->token)
	{
		temp = temp->next;
		printf("%s: token %d\n", minishell->token->token, i);
		if (minishell->token->token)
			free(minishell->token->token);
		if (minishell->token)
			free(minishell->token);
		i++;
		minishell->token = temp;
	}
}
