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
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_redir		t_redir;
typedef struct s_data		t_data;

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
typedef struct s_minishell
{
	t_token			*token;
	t_command		*command;
	t_data			*data;
}	t_minishell;

/*********** data utile ***********/
struct	s_data
{
	char		*line;
	char		**env;
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
struct	s_command
{
	char		**arg;
	t_redir		*redir;
	t_command	*next;
};

struct s_redir
{
	int		type;
	char	*file;
	t_redir	*next;
};

/*===================== init =====================*/
/* -------------- init_struct -------------- */
int		init_struct(t_minishell *minishell, char **environ);
int		put_prompt(char *line, t_minishell *minishell);

/*===================== parsing =====================*/
/*-------------- token -------------- */
int		tokening(t_minishell *minishell);

/* -------------- lexer -------------- */
void	lexeur(t_minishell *minishell);

/* -------------- parsing -------------- */
int		parsing(t_minishell *minishell);
int		creat_command(t_minishell *minishell);
int		redirect(t_command *command, t_token **token);
int		add_command(t_minishell *minishell, t_command **current);
int		add_arg(t_command *current, t_token *temp, int i);

/*===================== expand =====================*/
/* -------------- expand -------------- */
int		expand(t_minishell *minishell, t_command *command, int i, int j);
int		var_exist(t_minishell *minishell, char **str_new, int j, char **name);

/* -------------- del_quote -------------- */
int		remove_quote(t_command *command, int i, int j);

/*===================== exec =====================*/
/* -------------- exec -------------- */
int		exec(t_minishell *minishell);

/*===================== builtin =====================*/
void	echo(char **str);
void	show_environ(char **av);

/*===================== error/free =====================*/
/* -------------- error -------------- */
char	*return_null(t_minishell *minishell);
int		return_err_int(t_minishell *minishell, char *str);

/* -------------- free -------------- */
void	all_free(t_minishell *minishell);
void	free_command_redir_token(t_minishell *minishell);

/*||||||||||||||||||||| test |||||||||||||||||||||*/
/*--------------- test ----------------*/
void	show_commands(t_command *command, int i, int cmd_index);
void	show_lexeur(t_minishell *minishell);
void	show_token(t_minishell *minishell);

#endif
