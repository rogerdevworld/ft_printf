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

void	ft_percent(t_printf *ft_flags, int *length)
{
	int	padding;

	padding = ft_flags->width - 1;
	if (!ft_flags->dash && padding > 0)
	{
		while (padding-- > 0)
		{
			if (ft_flags->zero)
				ft_putchar('0', length);
			else
				ft_putchar(' ', length);
		}
	}
	ft_putchar('%', length);
	if (ft_flags->dash && padding > 0)
		while (padding-- > 0)
			ft_putchar(' ', length);
}
