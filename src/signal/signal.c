#include "minishell.h"

void	gst_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	signal_break(int sig, void (*gst_handler)(int))
{
	struct sigaction	sa;

	(void)sig;
	sa.sa_handler = gst_handler;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction (SIGINT, &sa, NULL);
}

void	ignore_signal(int sig)
{
	struct sigaction	sa;

	(void)sig;
	sa.sa_handler = SIG_IGN;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction (SIGQUIT, &sa, NULL);
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
	signal_break(SIGINT, gst_handler);
	ignore_signal(SIGQUIT);
	return (0);
}

void	restore_default_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
