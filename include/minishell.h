/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:16:39 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/25 16:58:41 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/include/libft.h"
# include <stdio.h>
/*readline*/
# include <readline/readline.h>
# include <readline/history.h>
/*signal*/
# include <signal.h>
/*errno*/
# include <errno.h>
/*opendir, readdir, closedir*/
# include <dirent.h>
/*terminal*/
# include <termios.h>
# include <sys/ioctl.h>
/*open*/
# include <fcntl.h>
/*wait, waitpid..*/
# include <sys/wait.h>
# include <sys/resource.h>
/*stat*/
# include <sys/stat.h>
/*joker*/
# include <sys/time.h>
# include <sys/types.h>

typedef struct s_minishell	t_minishell;
typedef struct s_cmd_pipe	t_cmd_pipe;
typedef struct s_traitement	t_traitement;
typedef struct s_history	t_history;
typedef struct s_cd_memorie	t_cd_memorie;

/*struct de recup */
typedef struct s_minishell
{
	t_cmd_pipe		*cmd_pipe;
	t_history		*history;
	t_traitement	*traitement;
	t_cd_memorie	*memorie_cd;
}	t_minishell;

/*struct a traiter*/
struct s_traitement
{
	char	**tab;
};

/*cd memorie*/
struct	s_cd_memorie
{
	char	*now;
	char	*before;
};

/*struct history*/
struct	s_history
{
	char		*ligne;
	t_history	*next;
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
	t_minishell	*minishell;
};

/*fonction pipe*/
int		verif_file(char **av, t_cmd_pipe *data, int ac);
int		exec_com(char *av, char **environ);

int		error_sys(t_cmd_pipe *data);
int		error_arg(void);
char	*error_com(char **path);

void	child_transi(char **environ, char *av, t_cmd_pipe *data);
void	child_last(char **environ, char *av, t_cmd_pipe *data);
void	order_management(int ac, char **av, char **environ, t_cmd_pipe *data);
void	wait_parent(t_cmd_pipe *data, int i);
void	close_fd(t_cmd_pipe *data);

/*here_doc*/
void	here_doc(int ac, char **av, char **environ, t_cmd_pipe *data);
int		recup_in(char **av);

#endif
