/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:37:44 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/12 15:30:19 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

int				ft_printf(char *format, ...);
unsigned int	format_unsigned_int(char c, va_list args, unsigned int count);
unsigned int	format_int(char c, va_list args, unsigned int count);
unsigned int	format_char(char c, va_list args, unsigned int count);
void			ft_putnbr_base_unsigned_long(unsigned long nbr,
					int fd, char *base);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_unsigned(unsigned int n, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_check_base(char *base);
void			ft_putnbr_fd(int n, int fd);
#endif
