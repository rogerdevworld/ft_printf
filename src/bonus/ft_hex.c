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

void	ft_hex(t_printf *ft_flags, va_list args, int *length, char spec)
{
	unsigned int num;
	int num_len;
	int zeros;
	int padding;
	int prefix_len;

	num = va_arg(args, unsigned int);
	num_len = ft_numlen_base(num, 16);
	zeros = 0;
	prefix_len = 0;
	if (ft_flags->hash && num != 0)
		prefix_len = 2;
	if (ft_flags->dot)
	{
		zeros = ft_flags->accuracy - num_len;
		if (zeros < 0)
			zeros = 0;
		ft_flags->zero = 0;
	}
	else if (ft_flags->zero && !ft_flags->dash)
	{
		zeros = ft_flags->width - num_len - prefix_len;
		if (zeros < 0)
			zeros = 0;
	}
	padding = ft_flags->width - num_len - zeros - prefix_len;
	if (num == 0 && ft_flags->dot && ft_flags->accuracy == 0)
	{
		while (padding-- > 0)
			ft_putchar(' ', length);
		return ;
	}
	if (!ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
	if (ft_flags->hash && num != 0)
	{
		ft_putchar('0', length);
		ft_putchar(spec, length);
	}
	while (zeros-- > 0)
		ft_putchar('0', length);
	if (num != 0 || !ft_flags->dot || ft_flags->accuracy != 0)
		ft_putnbr_base(num, 16, (spec == 'X'), length);
	if (ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
}