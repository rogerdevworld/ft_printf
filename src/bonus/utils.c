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

int	ft_numlen_base(unsigned long num, int base)
{
	int len;

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