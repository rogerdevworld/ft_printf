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

void	ft_apply_flags(const char **str, t_printf *ft_flags)
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

void	ft_apply_width(const char **str, t_printf *ft_flags)
{
	while (ft_isdigit(**str))
	{
		ft_flags->width = ft_flags->width * 10 + (**str - '0');
		(*str)++;
	}
}

void	ft_apply_precision(const char **str, t_printf *ft_flags)
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