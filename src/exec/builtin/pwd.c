#include "minishell.h"

void	print_emplacement(void)
{
	char	*w_dir;

	w_dir = getcwd (NULL, 0);
	printf ("%s\n", w_dir);
	return ;
}
