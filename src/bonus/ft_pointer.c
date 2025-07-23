/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:47 by rmarrero          #+#    #+#             */
/*   Updated: 2025/01/24 16:39:25 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/ft_printf_bonus.h"

void	ft_putstr(char *str, int *length)
{
	if (!str)
		return ;
	while (*str)
		ft_putchar(*str++, length);
}

void	ft_pointer(t_printf *ft_flags, va_list args, int *length)
{
	uintptr_t	ptr;
	char		buffer[20];
	int			i;
	int			padding;

	ptr = va_arg(args, uintptr_t);
	i = 0;
	if (!ptr)
		return ((void)(ft_putstr("(nil)", length)));
	ft_putstr("0x", length);
	while (ptr)
	{
		buffer[i++] = "0123456789abcdef"[ptr % 16];
		ptr /= 16;
	}
	padding = ft_flags->width - (i + 2);
	if (!ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
	while (i-- > 0)
		ft_putchar(buffer[i], length);
	if (ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
}
