#include "minishell.h"

static int	error_here_doc(void)
{
	return (1);
}

int	expand_here_doc(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (temp->file
			&& (temp->file[0] == '<' || temp->file[0] == '|'))
			return (error_here_doc());
		temp = temp->next;
	}
	return (0);
}
