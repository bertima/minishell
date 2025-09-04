A mettre dans parseur parsing

static void test_commands(t_minishell *minishell)
{
    t_command *cmd = minishell->command;
    int i = 1;

    while (cmd)
    {
        printf("=== Command %d ===\n", i);
        if (cmd->arg && cmd->arg[0])
            printf("Name: %s\n", cmd->arg[0]->token);
        else
            printf("Name: (null)\n");

        printf("Args: ");
        if (cmd->arg)
        {
            for (int j = 0; j < cmd->nbr_arg; j++)
            {
                if (cmd->arg[j])
                    printf("%s ", cmd->arg[j]->token);
            }
        }
        printf("\n");

        printf("Infile: %s\n", cmd->infile ? cmd->infile : "(null)");
        printf("Outfile: %s\n", cmd->outfile ? cmd->outfile : "(null)");
        printf("Append: %d\n", cmd->append);
        printf("Here_doc: %d\n", cmd->here_doc);
        printf("\n");

        cmd = cmd->next;
        i++;
    }
}
