#include "minishell.h"

int child(t_shell *shell, t_cmd *cmd)
{
    (void)shell;
    (void)cmd;
    if (dup2(cmd->fd_in, STDIN_FILENO))
        return (1);
    close (cmd->fd_in);
    if (dup2(cmd->fd_out, STDOUT_FILENO))
        return (1);
    close (cmd->fd_out);
    return (0);
}
