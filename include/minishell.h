/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:16:39 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/05 15:31:19 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
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

typedef struct s_minishell	t_minishell;
typedef struct s_cmd_pipe	t_cmd_pipe;
typedef struct s_token		t_token;
typedef struct s_builtin	t_builtin;
typedef struct s_command	t_command;
typedef struct s_redir		t_redir;
typedef struct s_data		t_data;
typedef struct s_local_var	t_local_var;

enum	e_type
{
	WORD,
	MORE,
	LESS,
	HERE_DOC,
	REDIRECT_A,
	PIPE,
};

/*struct de recup */
typedef struct s_minishell
{
	t_cmd_pipe		*cmd_pipe;
	t_token			*token;
	t_builtin		*builtin;
	t_command		*command;
	t_data			*data;
}	t_minishell;

/*data utile*/
struct	s_data
{
	char		*line;
	char		**env;
	t_local_var	*local_var;
};

struct	s_local_var
{
	char		name;
	char		value;
	t_local_var	*next;
};

/*struct a traiter*/
struct s_token
{
	char			*sentence;
	int				type;
	t_token			*next;
};

/*commande*/
struct	s_command
{
	char		**arg;
	t_redir		*redir;
	t_command	*next;
};

/*redirection*/
struct s_redir
{
	int		type;
	char	*file;
	t_redir	*next;

};

/*struct pipe*/
struct	s_cmd_pipe
{
	int			ac;
	int			pipefd[2];
	pid_t		pid;
	int			stock_fd;
	int			status;
	int			stop;
	int			fd_w;
	int			fd_r;
	int			exit_value;
};

struct	s_builtin
{
	char	redirect_in;
	char	redirect_out;
	char	*doc_here_in;
	char	*doc_here_out;
	char	*pipe;
	char	*echo;
	char	dollar;
};

/*============== error ==============*/
char	*return_null(t_minishell *minishell);
int		return_err_int(t_minishell *minishell, char *str);

/*============== free ==============*/
void	all_free(t_minishell *minishell);
void	free_command_redir_token(t_minishell *minishell);

/*============== exec ==============*/
int		exec(t_minishell *minishell);
int		expand(t_minishell *minishell, t_command *command, int i, int j);

/*============== builtin ==============*/
void	echo(char **str);

/*============== init_struct ==============*/
int		init_struct(t_minishell *minishell);
int		put_prompt(char *line, t_minishell *minishell);
int		cp_env(char ***env, char **environ);

/*============== token ==============*/
int		parsing(t_minishell *minishell);
int		tokening(t_minishell *minishell);

/*============== lexer ==============*/
void	lexeur(t_minishell *minishell);

/*============== parsing ==============*/
int		creat_command(t_minishell *minishell);
int		add_command(t_minishell *minishell, t_command **current);
int		add_arg(t_command *current, t_token *temp, int i);
int		redirect(t_command *command, t_token **token);

#endif
