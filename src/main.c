#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

t_shell	*get_shell_ptr(t_shell *new_ptr)
{
	static t_shell *ptr = NULL;

	if (new_ptr)
		ptr = new_ptr;
	return (ptr);
}

void	gst_handler(int sig)
{
	t_shell *shell = get_shell_ptr(NULL);

	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		if (shell && shell->data)
			shell->data->exit_code = 130;
	}
}

static void	programme(char *line, t_shell *shell)
{
	if (put_prompt(line, shell))
		return ;
	if (parsing(shell))
		return ;
	if (expand(shell, shell->cmd, 0, 0))
		return ;
	if (here_doc(shell, NULL))
		return ;
	exec(shell);
}

int	main(int ac, char **av, char **environ)
{
	char		*line;
	t_shell		shell;

	if (ac != 1 || !av[0])
		return (error_find_int(NULL, ARG_MINISHELL, 1, NULL));
	line = NULL;
	if (init_struct(&shell, environ))
		return (1);
	get_shell_ptr(&shell);
	signal_break(SIGINT, gst_handler);
	ignore_signal(SIGQUIT);
	while (1)
	{
		programme(line, &shell);
		free_command_redir_token_children(&shell);
	}
	all_free(&shell);
	return (0);
}
