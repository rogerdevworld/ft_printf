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

int	ft_calc_zeros(unsigned long num, int is_neg, t_printf *f)
{
	int	len;
	int	zeros;

	len = ft_numlen_base(num, 10);
	zeros = 0;
	if (f->dot)
	{
		zeros = f->accuracy - len;
		if (zeros < 0)
			zeros = 0;
		f->zero = 0;
	}
	else if (f->zero && !f->dash)
	{
		zeros = f->width - len;
		if (is_neg || f->sign || f->space)
			zeros--;
		if (zeros < 0)
			zeros = 0;
	}
	return (zeros);
}

void	ft_print_sign(int is_neg, t_printf *f, int *len)
{
	if (is_neg)
		ft_putchar('-', len);
	else
	{
		if (f->sign)
			ft_putchar('+', len);
		else if (f->space)
			ft_putchar(' ', len);
	}
}

void	ft_integer_zero_case(int is_neg, t_printf *f, int *len)
{
	int	total;
	int	padding;

	total = 0;
	if (is_neg || f->sign || f->space)
		total = 1;
	padding = f->width - total;
	if (!f->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', len);
	ft_print_sign(is_neg, f, len);
	if (f->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', len);
}

void	ft_print_integer(unsigned long abs_num, int is_neg, t_printf *f,
		int *len)
{
	int	zeros;
	int	num_len;
	int	total;
	int	padding;

	zeros = ft_calc_zeros(abs_num, is_neg, f);
	num_len = ft_numlen_base(abs_num, 10);
	total = num_len + zeros;
	if (is_neg || f->sign || f->space)
		total++;
	padding = f->width - total;
	if (abs_num == 0 && f->dot && f->accuracy == 0)
		return ((void)ft_integer_zero_case(is_neg, f, len));
	if (!f->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', len);
	ft_print_sign(is_neg, f, len);
	while (zeros-- > 0)
		ft_putchar('0', len);
	ft_putnbr_base(abs_num, 10, 0, len);
	if (f->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', len);
}

void	ft_integer(t_printf *ft_flags, va_list args, int *length)
{
	long			num;
	int				is_negative;
	unsigned long	abs_num;

	num = va_arg(args, int);
	if (num < 0)
	{
		is_negative = 1;
		abs_num = (unsigned long)(-num);
	}
	else
	{
		is_negative = 0;
		abs_num = (unsigned long)num;
	}
	ft_print_integer(abs_num, is_negative, ft_flags, length);
}
