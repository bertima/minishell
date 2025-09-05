A mettre dans parseur parsing

void	show_commands(t_command *command)
{
	int i;
	t_redir *redir;
	int cmd_index = 1;

	while (command)
	{
		printf("=== Command %d ===\n", cmd_index);
		if (command->arg && command->arg[0])
			printf("Name: %s\n", command->arg[0]);
		else
			printf("Name: (null)\n");

		// Affiche les arguments
		i = 0;
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

		// Affiche les redirections
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

		printf("\n");
		command = command->next;
		cmd_index++;
	}
}
