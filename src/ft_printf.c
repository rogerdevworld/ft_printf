/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:47 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/22 14:25:36 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

/* dejare el ft_printf para manejo de errores 
 * etc y llamar a las funciones finales */
int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		length;

	i = 0;
	length = 0;
	va_start(args, str);
	if (!*str)
		return (0);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i])
				is_flag(str[i], args, &length, &i);
			else
				break ;
		}
		else
			ft_putchar(str[i], &length);
		i++;
	}
	va_end(args);
	return (length);
}
