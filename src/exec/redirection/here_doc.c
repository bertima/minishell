#include "minishell.h"

static void	verif_expand_hd(t_redir *redir, char **arg)
{
	int	i;

	i = 0;
	while (arg[0] && arg[0][i])
	{
		if (arg[0][i] == '\'' || arg[0][i] == '\"')
		{
			redir->hd_expand = 1;
			break ;
		}
		i++;
	}
}

int	manage_here_doc(t_redir *redir)
{
	verif_expand_hd(redir, redir->file);
	if (loop_remove_quote(&redir->file, 0, 0))
		return (1);
	return (0);
}
