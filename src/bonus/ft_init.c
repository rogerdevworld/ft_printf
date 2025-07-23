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
