#include "minishell.h"

/*static char  **add_argument(char **arg, char *str, int j, int end)
{
    char    **temp;

    temp = calloc(ft_len_double_char(arg), sizeof(char *));
}

static int  new_arg(t_cmd *cmd, int *i, int j, char ***new)
{
    int     end;
    char    **new;

    while (cmd->arg[*i][j]) 
    {
        end = 0;
        if (ft_isspace(cmd->arg[*i][j]))
            j++;
        if (!cmd->arg[*i][j])
            break ;
        while (!ft_isspace(cmd->arg[*i][j + end]))
            end++;
        if (end > 0)
        {
            new = add_argument(cmd->arg, cmd->arg[*i], j, end);
                return (1);
        }
        j += end;
    }
    if (!new)
        return (0);
 //   if 
 //   ft_free_split(cmd->arg);
   // cmd->arg = new;
    return (0);

}*/

int expand_without_quote(t_shell *shell, t_cmd *cmd, int *i, int *j)
{
    char    **new;
    int     start;
    int     result;

    start = *j;
    new = NULL;
    while (cmd->arg[*i][*j])
    {
        if (cmd->arg[*i][*j] == '$')
	    {
		    result = exit_code_expand(shell, cmd->arg, i, j);
            if (result == 1)
			    return (1);
//            if (result == 2)
  //              return (0);
            else if (search_expand(shell, cmd, i, j))
                return (1);
        }
        (*j)++;
    }
//    if (new_arg(cmd, i, start, &new))
//        return (1);
    return (0);
}
