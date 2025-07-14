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

void	ft_char(t_printf *ft_flags, va_list args, int *length)
{
	char	c;
	int		padding;

	c = (char)va_arg(args, int);
	padding = ft_flags->width - 1;
	if (ft_flags->dash)
	{
		ft_putchar(c, length);
		while (padding-- > 0)
			ft_putchar(' ', length);
	}
	else
	{
		while (padding-- > 0)
			if (ft_flags->zero)
				ft_putchar('0', length);
			else
			ft_putchar(' ', length);
		ft_putchar(c, length);
	}
}