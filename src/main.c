/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:10 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/25 17:01:08 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recup_wd(t_cd_memorie *cd_mem)
{
	char	*w_dir;
	char	**split_path;
	int		len;

	w_dir = getcwd(NULL, 0);
	if (!w_dir)
		return (NULL);
	cd_mem->now = w_dir;
	split_path = ft_split(w_dir, "/");
	if (!split_path)
	{
		free(cd_mem);
		return (NULL);
	}
	len = ft_len_double_char(split_path);
	w_dir = ft_strjoin_var(3, "~/", split_path[len - 1], "$ ");
	if (!w_dir)
		return (NULL);
	return (w_dir);
}

int	put_prompt(char *line, t_cd_memorie *cd_mem)
{
	char	*w_dir;

	w_dir = recup_wd(cd_mem);
	if (!w_dir)
		return (1);
	line = readline(w_dir);
	if (!line)
	{
		perror("");
		return (1);
	}
	if (*line)
		add_history(line);
	printf("%s\n", line);
	free(line);
	free(w_dir);
	line = NULL;
	w_dir = NULL;
	return (0);
}

int	main(void)
{
	char			*line;
	t_cd_memorie	cd_mem;

	line = NULL;
	while (1)
	{
		if (put_prompt(line, &cd_mem))
			break ;
	}
	rl_clear_history();
	return (0);
}
