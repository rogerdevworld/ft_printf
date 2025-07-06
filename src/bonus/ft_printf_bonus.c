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

int	ft_printf(const char *str, ...)
{
	va_list		args;
	t_printf	ft_flags;
	int			length;

	length = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_initialise_flags(&ft_flags);
			ft_apply_flags(&str, &ft_flags);
			ft_apply_width(&str, &ft_flags);
			ft_apply_precision(&str, &ft_flags);
			if (ft_validation(*str))
			{
				if (*str == 'c')
					ft_char(&ft_flags, args, &length);
				else if (*str == 's')
					ft_string(&ft_flags, args, &length);
				else if (*str == 'd' || *str == 'i')
					ft_integer(&ft_flags, args, &length);
				else if (*str == 'u')
					ft_unsigned(&ft_flags, args, &length);
				else if (*str == 'p')
					ft_pointer(&ft_flags, args, &length);
				else if (*str == 'x' || *str == 'X')
					ft_hex(&ft_flags, args, &length, *str);
				else if (*str == '%')
					ft_percent(&ft_flags, &length);
				str++;
			}
		}
		else
			ft_putchar(*str++, &length);
	}
	va_end(args);
	return (length);
}

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

void	ft_string(t_printf *ft_flags, va_list args, int *length)
{
	char	*str;
	int		len;
	int		padding;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (ft_flags->dot && ft_flags->accuracy < len)
		len = ft_flags->accuracy;
	padding = ft_flags->width - len;
	if (!ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
	write(1, str, len);
	(*length) += len;
	if (ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
}

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

void	ft_unsigned(t_printf *ft_flags, va_list args, int *length)
{
	unsigned long	num;
	int				num_len;
	int				zeros;
	int				padding;

	num = va_arg(args, unsigned int);
	num_len = ft_numlen_base(num, 10);
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
		if (zeros < 0)
			zeros = 0;
	}
	padding = ft_flags->width - num_len - zeros;
	if (num == 0 && ft_flags->dot && ft_flags->accuracy == 0)
	{
		while (padding-- > 0)
			ft_putchar(' ', length);
		return ;
	}
	if (!ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
	while (zeros-- > 0)
		ft_putchar('0', length);
	if (num != 0 || !ft_flags->dot || ft_flags->accuracy != 0)
		ft_putnbr_base(num, 10, 0, length);
	if (ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
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
	{
		ft_putstr("(nil)", length);
		return ;
	}
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

void	ft_hex(t_printf *ft_flags, va_list args, int *length, char spec)
{
	unsigned int	num;
	int				num_len;
	int				zeros;
	int				padding;
	int				prefix_len;

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

void	ft_percent(t_printf *ft_flags, int *length)
{
	int	padding;

	padding = ft_flags->width - 1;
	if (!ft_flags->dash && padding > 0)
	{
		while (padding-- > 0)
			ft_putchar(ft_flags->zero ? '0' : ' ', length);
	}
	ft_putchar('%', length);
	if (ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
}