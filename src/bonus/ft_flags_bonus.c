/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:23 by rmarrero          #+#    #+#             */
/*   Updated: 2024/11/29 16:53:48 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/ft_printf_bonus.h"

/* %char hunter */
void is_flag(char c, va_list args, int *length, int *flag, ft_printf *ft_flags)
{
    if (c == 'c')
        ft_putchar((char)va_arg(args, int), length, flag);
    else if (c == 's')
        ft_putstr(va_arg(args, char *), length, flag, ft_flags);
    else if (c == 'p')
        ft_pointer(va_arg(args, uintptr_t), length, flag, ft_flags);
    else if (c == 'u')
        ft_unsigned_putnbr(va_arg(args, unsigned int), length, flag, ft_flags);
    else if (c == 'i' || c == 'd')
        ft_putnbr(va_arg(args, int), length, flag, ft_flags);
    else if (c == 'x')
        ft_hex(va_arg(args, unsigned int), length, 'x', flag, ft_flags);
    else if (c == 'X')
        ft_hex(va_arg(args, unsigned int), length, 'X', flag, ft_flags);
    else if (c == '%')
        ft_putchar('%', length, flag);
}


/* %u Print an unsigned decimal number (base 10). */
void	ft_unsigned_putnbr(unsigned int unsgined_nbr, int *length, int *flag, ft_printf *ft_flags)
{
	if (unsgined_nbr > 9)
		ft_unsigned_putnbr(unsgined_nbr / 10, length, flag, ft_flags);
	ft_putchar(unsgined_nbr % 10 + '0', length, flag, ft_flags);
}
