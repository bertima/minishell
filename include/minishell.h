#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdint.h>
# include <stdio.h>
# include <errno.h>

/*=== readline ===*/
# include <readline/readline.h>
# include <readline/history.h>

/*=== signal ===*/
# include <signal.h>

/*=== opendir, readdir, closedir ===*/
# include <dirent.h>

/*=== terminal ===*/
# include <termios.h>
# include <sys/ioctl.h>

/*=== files ===*/
# include <sys/stat.h>
# include <fcntl.h>

/*=== wait, waitpid.. ===*/
# include <sys/wait.h>
# include <sys/resource.h>

/*=== pid_t, size_t... ===*/
# include <sys/time.h>
# include <sys/types.h>

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;
typedef struct s_data		t_data;
typedef struct s_expand		t_expand;

enum	e_type
{
	WORD,
	MORE,
	LESS,
	HERE_DOC,
	REDIRECT_A,
	PIPE,
};

/*********** struct de recup ***********/
struct s_shell
{
	t_token			*token;
	t_cmd			*cmd;
	t_data			*data;
	t_expand		*expand;
};

/*********** data utile ***********/
struct	s_data
{
	char		*line;
	char		**env;
	int			fd_stock_in;
	int			fd_stock_out;
	int			pipefd[2];
	int			exit_code;
};

/*********** struct token ***********/
struct s_token
{
	char			*sentence;
	int				type;
	t_token			*next;
};

/*********** commande ***********/
struct	s_cmd
{
	char		**arg;
	int			fd_in;
	int			fd_out;
	t_redir		*redir;
	t_cmd		*next;
};

struct s_redir
{
	int		type;
	int		hd_expand;
	char	*file_temp;
	char	*before_exp;
	char	**file;
	t_redir	*next;
};

/*===================== init =====================*/
/* -------------- init_struct -------------- */
int		init_struct(t_shell *shell, char **environ);
int		put_prompt(char *line, t_shell *shell);

/*===================== parsing =====================*/
/*-------------- token -------------- */
int		tokening(t_shell *shell);
/* ............. utils ............. */
int		metachar(char *line, int index, int *len);

/* -------------- lexer -------------- */
int		lexeur(t_shell *shell);

/* -------------- parsing -------------- */
int		parsing(t_shell *shell);
/* ............. utils ............. */
int		creat_command(t_shell *shell);
int		manage_redirect_token(t_cmd *cmd, t_token **token);
int		add_command(t_shell *shell, t_cmd **current);
int		add_arg(t_cmd *current, t_token *temp, int i);

/*===================== signaux =====================*/
/* -------------- signaux -------------- */
void	signal_break(int sig, void (*gst_handler)(int));
void	ignore_signal(int sig);
void	gst_handler(int sig);

/*===================== expand =====================*/
/* -------------- expand -------------- */
int		expand(t_shell *shell, t_cmd *cmd, int i, int j);
/* ............. utils ............. */
int		loop_remove_quote(char ***arg, int stock, int i);
int		expand_in_arg(t_shell *shell, char ***arg, int *i, int *j);
int		insert_arg_expand(char ***arg, int *start_end, int *i, int *j);
int		expand_without_quote(t_shell *shell, char ***arg, int *i, int *j);
int		quote_process(t_shell *shell, char ***arg, int *i, int *j);

/* -------------- del_quote -------------- */
int		remove_quote(char **str, int *start);

/* -------------- utils -------------- */
char	*search_name(char *str, int start);
int		search_expand(t_shell *shell, char ***arg, int *i, int *j);
int		exit_code_expand(t_shell *shell, char **arg, int *i, int *end);
int		suppress_arg(char ***arg, int *i);

/*===================== redirection =====================*/
/* -------------- redirection -------------- */
int		redirection_verif(t_shell *shell, t_cmd *temp_cmd);
int		creat_here_doc(t_shell *shell, t_cmd *cmd, char *temp_file, int fd);
int		manage_delimiter_hd(t_redir *redir);
int		generator_of_file_name(char **str, char *nbr_count, char *nbr_pid);

/*===================== exec =====================*/
/* -------------- exec -------------- */
int		exec(t_shell *shell, int i);
int		exec_com(char **av, char **environ);
int		execut_command(t_shell *shell, t_cmd *cmd);
int		exec_builtin(t_shell *shell, t_cmd **cmd);
int		redirect_command(t_shell *shell, t_cmd **cmd, int i);

/*===================== builtin =====================*/
void	echo(char **str);
int		strlen_av(char **av);
void	show_environ(char **av);
void	print_emplacement(void);
void	end_prog(t_shell *shell, char **av);
void	dep_fd(char **av);
void	export(char **env, char **av);
void	unset(char **env, char **av);

/*===================== error =====================*/
/* -------------- error -------------- */
char	*return_null(t_shell *shell);
int		return_err_int(t_shell *shell, char *str);

/* -------------- free -------------- */
void	all_free(t_shell *shell);
void	free_command_redir_token(t_shell *shell);
void	free_expand(t_shell *shell);

/*||||||||||||||||||||| test |||||||||||||||||||||*/
/*--------------- test ----------------*/
void	show_commands(t_cmd *cmd, int i, int cmd_index);
void	show_lexeur(t_shell *shell);
void	show_token(t_shell *shell);

#endif
