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
typedef struct s_children	t_children;

/*********** metachar ***********/
enum	e_type
{
	WORD,
	MORE,
	LESS,
	HERE_DOC,
	REDIRECT_A,
	PIPE,
};

/*********** error ***********/
enum	e_error
{
	ARG_MINISHELL,
	META,
	MALLOC,
	QUOTE,
	AMBIGUOUS,
};

/*********** struct de recup ***********/
struct s_shell
{
	t_token			*token;
	t_cmd			*cmd;
	t_data			*data;
	t_expand		*expand;
	t_children		*children;
};

/*********** data utile ***********/
struct	s_data
{
	char		*line;
	char		*w_dir_prompt;
	char		**env;
	char		**exp;
	int			fd_stock_in;
	int			fd_stock_out;
	int			exit_code;
};

/*********** children ***********/
struct s_children
{
	int			fd_transi;
	int			nbr_cmd;
	int			last_pid;
	int			status;
	int			pipefd[2];
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
void	restore_default_signals(void);
void	ignore_signal(int sig);
void	gst_handler(int sig);
int		ft_sig(int status);

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
int		here_doc(t_shell *shell, t_cmd *temp_cmd);
int		creat_here_doc(t_shell *shell, t_cmd *cmd, char *temp_file, int fd);
int		manage_delimiter_hd(t_redir *redir);
int		generator_of_file_name(char **str, char *nbr_count, char *nbr_pid);

/*===================== exec =====================*/
/* -------------- exec -------------- */
int		exec(t_shell *shell);
int		exec_com(t_shell *shell, char **av, char **environ);
int		execut_command(t_shell *shell, t_cmd *cmd, int status);
int		verif_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);
int		bultin(t_shell *shell, t_cmd *cmd);

/* -------------- redir -------------- */
int		redirect_std(t_shell *shell);
int		redirect_cmd(t_shell *shell, t_cmd *temp_cmd);
void	close_fd(int *fd);
void	close_stock(t_shell *shell);
void	close_fd_cmd_shell(t_shell *shell, t_cmd *cmd);

/* -------------- child -------------- */
void	creat_child(t_shell *shell, t_cmd *cmd, int pid);
void	wait_parent(t_shell *shell);

/*===================== builtin =====================*/
/* -------------- echo -------------- */
void	echo(char **str);

/* -------------- env -------------- */
void	show_environ(char **av);

/* -------------- pwd -------------- */
void	print_emplacement(t_shell *shell);

/* -------------- exit -------------- */
void	end_prog(t_shell *shell, char **av);

/* -------------- cd -------------- */
char	**dep_fd(char **av, char **env);
char	*return_oldpwd(char **env);
char	*stock_pwd(const char *s, int i);
char	*get_env_value(char **env, const char *key);
char	*return_home(char *str);

/* -------------- export -------------- */
void	export(t_shell *shell, char **args, char **tmp);
int		check_sign(char *av);
void	show_ex(char **av);
void	tri_bubule(char **ex);
int		error_export(char **av);
char	**normalize_export(char **exp);
char	**cp_ex(char **env);
char	*remove_quotes_value(char *var);
int		var_exists(char **env, char *var);
char	*quote_value(char *var);
int		var_name_match(char *s1, char *s2);
int		is_quoted(char *value);

/* -------------- unset -------------- */
char	**unset(char **env, char **av);

/* -------------- utility -------------- */
int		strlen_av(char **av);

/*===================== error =====================*/
/* -------------- error -------------- */
char	*error_find_char(t_shell *shell, int e_code, int code_err, char *str);
int		error_find_int(t_shell *shell, int e_code, int code_err, char *str);

/* -------------- free -------------- */
void	all_free(t_shell *shell);
void	free_command_redir_token_children(t_shell *shell);
void	free_expand(t_shell *shell);

/*||||||||||||||||||||| test |||||||||||||||||||||*/
/*--------------- test ----------------*/
void	show_commands(t_cmd *cmd, int i, int cmd_index);
void	show_lexeur(t_shell *shell);
void	show_token(t_shell *shell);

#endif
