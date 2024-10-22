/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:23 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/22 14:12:15 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

/* %char hunter */
void	is_flag(char c, va_list args, int *length, int *i)
{
	if (c == 'c')
		ft_putchar((char)va_arg(args, int), length);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), length);
	else if (c == 'p')
		ft_pointer(va_arg(args, uintptr_t), length);
	else if (c == 'u')
		ft_unsigned_putnbr(va_arg(args, unsigned int), length);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), length);
	else if (c == 'x')
		ft_hex(va_arg(args, unsigned int), length, 'x');
	else if (c == 'X')
		ft_hex(va_arg(args, unsigned int), length, 'X');
	else if (c == '%')
		ft_putchar('%', length);
	else
		(*i)--;
}

/* %u Print an unsigned decimal number (base 10). */
void	ft_unsigned_putnbr(unsigned int unsgined_nbr, int *length)
{
	if (unsgined_nbr > 9)
		ft_unsigned_putnbr(unsgined_nbr / 10, length);
	ft_putchar(unsgined_nbr % 10 + '0', length);
}
