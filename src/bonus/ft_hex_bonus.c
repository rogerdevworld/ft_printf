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

void	ft_calculate_hex_info(t_hex_info *info, t_printf *ft_flags,
		unsigned int num)
{
	info->num_len = ft_numlen_base(num, 16);
	info->prefix_len = 0;
	if (ft_flags->hash && num != 0)
		info->prefix_len = 2;
	info->zeros = 0;
	if (ft_flags->dot)
	{
		info->zeros = ft_flags->accuracy - info->num_len;
		if (info->zeros < 0)
			info->zeros = 0;
		ft_flags->zero = 0;
	}
	else if (ft_flags->zero && !ft_flags->dash)
	{
		info->zeros = ft_flags->width - info->num_len - info->prefix_len;
		if (info->zeros < 0)
			info->zeros = 0;
	}
	info->padding = ft_flags->width - info->num_len - info->zeros
		- info->prefix_len;
}

void	ft_print_hex_content(t_printf *ft_flags, t_hex_info *info,
		unsigned int num, int *length)
{
	if (ft_flags->hash && num != 0)
	{
		ft_putchar('0', length);
		if (info->is_uppercase)
			ft_putchar('X', length);
		else
			ft_putchar('x', length);
	}
	while (info->zeros-- > 0)
		ft_putchar('0', length);
	if (num != 0 || !ft_flags->dot || ft_flags->accuracy != 0)
		ft_putnbr_base(num, 16, info->is_uppercase, length);
}

void	ft_print_hex(t_printf *ft_flags, t_hex_info *info, unsigned int num,
		int *length)
{
	if (!ft_flags->dash && info->padding > 0)
		while (info->padding-- > 0)
			ft_putchar(' ', length);
	ft_print_hex_content(ft_flags, info, num, length);
	if (ft_flags->dash && info->padding > 0)
		while (info->padding-- > 0)
			ft_putchar(' ', length);
}

void	ft_hex(t_printf *ft_flags, va_list args, int *length, char spec)
{
	unsigned int	num;
	t_hex_info		info;

	num = va_arg(args, unsigned int);
	info.is_uppercase = (spec == 'X');
	ft_calculate_hex_info(&info, ft_flags, num);
	if (num == 0 && ft_flags->dot && ft_flags->accuracy == 0)
	{
		while (info.padding-- > 0)
			ft_putchar(' ', length);
		return ;
	}
	ft_print_hex(ft_flags, &info, num, length);
}
