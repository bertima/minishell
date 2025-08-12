/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:33:19 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/21 09:21:21 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		compte;
	int		stop;
	char	cc;

	i = 0;
	compte = 0;
	cc = (char)c;
	while (s[i])
	{
		if (s[i] == cc)
		{
			stop = i;
			compte++;
		}
		i++;
	}
	if (compte > 0)
		return ((char *)&s[stop]);
	if (cc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
