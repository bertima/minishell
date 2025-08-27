/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:16:39 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/27 15:52:27 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/include/libft.h"
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
typedef struct s_traitement	t_traitement;
typedef struct s_cd_memorie	t_cd_memorie;
typedef struct s_builtin	t_builtin;

/*struct de recup */
typedef struct s_minishell
{
	t_cmd_pipe		*cmd_pipe;
	t_traitement	*traitement;
	t_cd_memorie	*memorie_cd;
	t_builtin		*builtin;
}	t_minishell;

/*struct a traiter*/
struct s_traitement
{
	char	**cmd_tab;
	char	*line;
};

/*cd memorie*/
struct	s_cd_memorie
{
	char	*now;
	char	*before;
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
	char	dollar;
	//signaux
};

/*=== error ===*/
void	stop_free(t_minishell *minishell);
char	*return_null(t_minishell *minishell);
int		return_err_int(t_minishell *minishell);

/*============== exec ==============*/
int		exec(t_minishell *minishell, t_traitement *traitement);
void	echo(t_minishell *minishell);

/*=== init_struct ===*/
int		init_struct(t_minishell *minishell);
int		put_prompt(char *line, t_minishell *minishell);

/*============== parsing ==============*/
int		parsing(t_minishell *minishell, t_traitement *traitement);
int		search_quote(t_traitement *traitement);

#endif
