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

static void	handle_format(const char **str, va_list args, int *length)
{
	t_printf	ft_flags;

	ft_initialise_flags(&ft_flags);
	ft_apply_flags(str, &ft_flags);
	ft_apply_width(str, &ft_flags);
	ft_apply_precision(str, &ft_flags);
	if (ft_validation(**str))
	{
		if (**str == 'c')
			ft_char(&ft_flags, args, length);
		else if (**str == 's')
			ft_string(&ft_flags, args, length);
		else if (**str == 'd' || **str == 'i')
			ft_integer(&ft_flags, args, length);
		else if (**str == 'u')
			ft_unsigned(&ft_flags, args, length);
		else if (**str == 'p')
			ft_pointer(&ft_flags, args, length);
		else if (**str == 'x' || **str == 'X')
			ft_hex(&ft_flags, args, length, **str);
		else if (**str == '%')
			ft_percent(&ft_flags, length);
		(*str)++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		length;

	length = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			handle_format(&str, args, &length);
		}
		else
			ft_putchar(*str++, &length);
	}
	va_end(args);
	return (length);
}
