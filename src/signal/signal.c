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