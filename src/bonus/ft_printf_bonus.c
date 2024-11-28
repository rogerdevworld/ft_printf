/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:47 by rmarrero          #+#    #+#             */
/*   Updated: 2024/11/26 16:23:01 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/ft_printf.h"

/* struct bonus */
ft_printf *ft_initialise_flags(ft_printf *ft_flags)                       
{                       
      ft_flags->width = 0;     
      ft_flags->accuracy = 0;                        
      ft_flags->zero = 0;                        
      ft_flags->dot = 0;                        
      ft_flags->dash = 0;                        
      ft_flags->total_lenght = 0;                        
      ft_flags->sign = 0;                        
      ft_flags->is_zero = 0;                        
      ft_flags->percen = 0;                        
      ft_flags->space = 0;                        
      return (ft_flags);                       
}

/* dejare el ft_printf para manejo de errores 
 * etc y llamar a las funciones finales */
int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		length;
	int		flag;
	ft_printf *ft_flags;
                       
   ft_flags = (t_print *)malloc(sizeof(t_print));                        
   if (!ft_flags)                         
       return (-1);
   ft_initialise_flags(ft_flags)
	i = 0;
	length = 0;
	flag = 1;
	va_start(ft_flags->args, str);
	if (!*str)
		return (0);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i])
				if (ft_validation(str[i]) == 1)
					is_flag(str[i], args, &length, &flag);
				else
					return (-1);
			else
				break ;
		}
		else
			ft_putchar(str[i], &length, &flag);
		if (flag == -1)
			return (-1);
		i++;
	}
	va_end(args);
	return (length);
}
