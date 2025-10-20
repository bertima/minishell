#include "minishell.h"

void	setup_parent_signal(void)
{
	signal(SIGINT, gst_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	reset_child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

int	ft_sig(int status)
{
	int		sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 19);
			return (131);
		}
		else if (sig == SIGINT)
		{
			write(2, "\n", 1);
			return (130);
		}
	}
	return (0);
}
