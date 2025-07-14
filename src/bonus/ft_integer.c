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

void	ft_integer(t_printf *ft_flags, va_list args, int *length)
{
	long			num;
	int				is_negative;
	unsigned long	abs_num;
	int				num_len;
	int				zeros;
	int				padding;
	int				total_len;

	num = va_arg(args, int);
	is_negative = num < 0;
	abs_num = is_negative ? -num : num;
	num_len = ft_numlen_base(abs_num, 10);
	zeros = 0;
	if (ft_flags->dot)
	{
		zeros = ft_flags->accuracy - num_len;
		if (zeros < 0)
			zeros = 0;
		ft_flags->zero = 0;
	}
	else if (ft_flags->zero && !ft_flags->dash)
	{
		zeros = ft_flags->width - num_len;
		if (is_negative || ft_flags->sign || ft_flags->space)
			zeros--;
		if (zeros < 0)
			zeros = 0;
	}
	total_len = num_len + zeros;
	if (is_negative || ft_flags->sign || ft_flags->space)
		total_len++;
	padding = ft_flags->width - total_len;
	if (abs_num == 0 && ft_flags->dot && ft_flags->accuracy == 0)
	{
		total_len = 0;
		if (is_negative || ft_flags->sign || ft_flags->space)
			total_len = 1;
		padding = ft_flags->width - total_len;
		if (!ft_flags->dash && padding > 0)
			while (padding-- > 0)
				ft_putchar(' ', length);
		if (is_negative)
			ft_putchar('-', length);
		else if (ft_flags->sign)
			ft_putchar('+', length);
		else if (ft_flags->space)
			ft_putchar(' ', length);
		if (ft_flags->dash && padding > 0)
			while (padding-- > 0)
				ft_putchar(' ', length);
		return ;
	}
	if (!ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
	if (is_negative)
		ft_putchar('-', length);
	else if (ft_flags->sign)
		ft_putchar('+', length);
	else if (ft_flags->space)
		ft_putchar(' ', length);
	while (zeros-- > 0)
		ft_putchar('0', length);
	if (abs_num != 0 || !ft_flags->dot || ft_flags->accuracy != 0)
		ft_putnbr_base(abs_num, 10, 0, length);
	if (ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
}