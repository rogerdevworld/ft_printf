/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:15:26 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/22 14:35:05 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../libft.h"

typedef struct s_printf
{
	int	width;
	int	accuracy;
	int	zero;
	int	dot;
	int	dash;
	int	total_length;
	int	sign;
	int	is_zero;
	int	percent;
	int	space;
	int	hash;
}		t_printf;

typedef struct s_hex_info
{
	int	num_len;
	int	zeros;
	int	padding;
	int	prefix_len;
	int	is_uppercase;
}		t_hex_info;
/* Main function */
int		ft_printf(const char *str, ...);

/* Initialization */
void	ft_initialise_flags(t_printf *ft_flags);

/* Flag handlers */
void	ft_char(t_printf *ft_flags, va_list args, int *length);
void	ft_string(t_printf *ft_flags, va_list args, int *length);
void	ft_integer(t_printf *ft_flags, va_list args, int *length);
void	ft_pointer(t_printf *ft_flags, va_list args, int *length);
void	ft_hex(t_printf *ft_flags, va_list args, int *length, char spec);
void	ft_unsigned(t_printf *ft_flags, va_list args, int *length);
void	ft_percent(t_printf *ft_flags, int *length);

// -- apply -- //
void	ft_apply_width(const char **str, t_printf *ft_flags);
void	ft_apply_flags(const char **str, t_printf *ft_flags);
void	ft_apply_precision(const char **str, t_printf *ft_flags);

// -- Utils -- //
int		ft_numlen(long num);
void	ft_putnbr(long n, int *length);
int		ft_numlen_base(unsigned long num, int base);
void	ft_putnbr_base(unsigned long n, int base, int uppercase, int *length);

int		ft_validation(char c);
void	ft_putchar(char c, int *length);
void	ft_putstr(char *str, int *length);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);

#endif