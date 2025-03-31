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

void	ft_initialise_flags(t_printf *ft_flags)
{
	ft_flags->width = 0;
	ft_flags->accuracy = -1;
	ft_flags->zero = 0;
	ft_flags->dot = 0;
	ft_flags->dash = 0;
	ft_flags->total_length = 0;
	ft_flags->sign = 0;
	ft_flags->is_zero = 0;
	ft_flags->percent = 0;
	ft_flags->space = 0;
	ft_flags->hash = 0;
}

static void	parse_flags(const char **str, t_printf *ft_flags)
{
	while (**str == '-' || **str == '0' || **str == '#' || **str == ' '
		|| **str == '+')
	{
		if (**str == '-')
			ft_flags->dash = 1;
		else if (**str == '0')
			ft_flags->zero = 1;
		else if (**str == '#')
			ft_flags->hash = 1;
		else if (**str == ' ')
			ft_flags->space = 1;
		else if (**str == '+')
			ft_flags->sign = 1;
		(*str)++;
	}
}

static void	parse_width(const char **str, t_printf *ft_flags)
{
	while (ft_isdigit(**str))
	{
		ft_flags->width = ft_flags->width * 10 + (**str - '0');
		(*str)++;
	}
}

static void	parse_precision(const char **str, t_printf *ft_flags)
{
	if (**str == '.')
	{
		ft_flags->dot = 1;
		(*str)++;
		ft_flags->accuracy = 0;
		while (ft_isdigit(**str))
		{
			ft_flags->accuracy = ft_flags->accuracy * 10 + (**str - '0');
			(*str)++;
		}
	}
}

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
			parse_flags(&str, &ft_flags);
			parse_width(&str, &ft_flags);
			parse_precision(&str, &ft_flags);
			if (ft_validation(*str))
			{
				if (*str == 'c')
					handle_char(&ft_flags, args, &length);
				else if (*str == 's')
					handle_string(&ft_flags, args, &length);
				else if (*str == 'd' || *str == 'i')
					handle_integer(&ft_flags, args, &length);
				else if (*str == 'u')
					handle_unsigned(&ft_flags, args, &length);
				else if (*str == 'p')
					handle_pointer(&ft_flags, args, &length);
				else if (*str == 'x' || *str == 'X')
					handle_hex(&ft_flags, args, &length, *str);
				else if (*str == '%')
					handle_percent(&ft_flags, &length);
				str++;
			}
		}
		else
			ft_putchar(*str++, &length);
	}
	va_end(args);
	return (length);
}

void	handle_char(t_printf *ft_flags, va_list args, int *length)
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

void	handle_string(t_printf *ft_flags, va_list args, int *length)
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

void	handle_integer(t_printf *ft_flags, va_list args, int *length)
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

void	ft_putnbr_base(unsigned long n, int base, int uppercase, int *length)
{
	const char	*digits;

	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	if (n >= (unsigned long)base)
		ft_putnbr_base(n / base, base, uppercase, length);
	ft_putchar(digits[n % base], length);
}

void	handle_unsigned(t_printf *ft_flags, va_list args, int *length)
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

void	handle_pointer(t_printf *ft_flags, va_list args, int *length)
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

void	handle_hex(t_printf *ft_flags, va_list args, int *length, char spec)
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

int	ft_numlen_base(unsigned long num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		len++;
		num /= base;
	}
	return (len);
}

void	handle_percent(t_printf *ft_flags, int *length)
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

void	ft_putchar(char c, int *length)
{
	write(1, &c, 1);
	(*length)++;
}

void	ft_putstr(char *str, int *length)
{
	if (!str)
		return ;
	while (*str)
		ft_putchar(*str++, length);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_numlen(long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

void	ft_putnbr(long n, int *length)
{
	if (n < 0)
	{
		ft_putchar('-', length);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10, length);
	ft_putchar(n % 10 + '0', length);
}
