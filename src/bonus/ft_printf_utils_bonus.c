/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:07:36 by rmarrero          #+#    #+#             */
/*   Updated: 2024/11/26 16:23:14 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/ft_printf_bonus.h"

/* %c Prints a single character. */
void	ft_putchar(char character, int *length, int *flag)
{
	if (write(1, &character, 1) == -1)
	{
		(*flag) = -1;
		return ;
	}
	(*length)++;
}

/* %s Prints a string (as defined by default in C) */
void ft_putstr(char *args, int *length, int *flag, t_printf *ft_flags)
{
    size_t i = 0;
    int len = 0;

    // Si el string es NULL, imprimir "(null)"
    if (!args)
    {
        if (write(1, "(null)", 6) == -1)
        {
            (*flag) = -1;
            return ;
        }
        (*length) += 6;
        return ;
    }

    // Calcular la longitud de la cadena
    while (args[len])
        len++;

    // Si hay precisión y es menor que la longitud de la cadena, truncar
    if (ft_flags->accuracy >= 0 && ft_flags->accuracy < len)
        len = ft_flags->accuracy;

    // Rellenar con espacios si el ancho es mayor que la longitud de la cadena
    int padding = ft_flags->width - len;
    if (padding > 0 && !ft_flags->dash)  // Si no hay `-`, rellenamos con espacios
    {
        for (int i = 0; i < padding; i++)
            ft_putchar(' ', length, flag);  // Rellenar con espacios
    }

    // Imprimir la cadena (hasta la longitud determinada por la precisión)
    for (i = 0; i < len; i++)
    {
        ft_putchar(args[i], length, flag);
    }

    // Rellenar con espacios si hay ancho restante y el flag `-` está presente (alineación a la izquierda)
    if (padding > 0 && ft_flags->dash)
    {
        for (int i = 0; i < padding; i++)
            ft_putchar(' ', length, flag);
    }
}


/* 
- %d Prints a decimal number (base 10).
- %i Prints an integer in base 10.
*/
void ft_putnbr(int nbr, int *length, int *flag, ft_printf *ft_flags)
{
    if (nbr == -2147483648)  // Caso especial para el valor mínimo de un entero
    {
        if (write(1, "-2147483648", 11) == -1)
        {
            (*flag) = -1;
            return ;
        }
        (*length) += 11;
        return ;
    }
    
    int is_negative = nbr < 0;
    unsigned int abs_num = is_negative ? -nbr : nbr;
    
    // Calcular la longitud del número
    int len = 0;
    unsigned int temp_num = abs_num;
    while (temp_num > 0)
    {
        len++;
        temp_num /= 10;
    }
    
    if (is_negative)
        len++;  // Contar el signo '-' en caso de números negativos

    // Rellenar con espacios o ceros (si el flag '0' está presente)
    int padding = ft_flags->width - len;
    if (padding > 0 && !ft_flags->dash && !ft_flags->zero)
    {
        for (int i = 0; i < padding; i++)
            ft_putchar(' ', length, flag);
    }
    
    // Si el número es negativo, imprimir el signo '-'
    if (is_negative)
        ft_putchar('-', length, flag);
    
    // Imprimir el número
    if (nbr == 0)  // Caso especial para el 0
        ft_putchar('0', length, flag);
    else
        ft_putnbr(abs_num, length, flag);  // Llamada recursiva para imprimir el número
    
    // Rellenar con ceros si el flag '0' está presente
    if (padding > 0 && ft_flags->zero && !ft_flags->dash)
    {
        for (int i = 0; i < padding; i++)
            ft_putchar('0', length, flag);
    }
    
    // Rellenar con espacios si el flag `-` está presente (alineación a la izquierda)
    if (padding > 0 && ft_flags->dash)
    {
        for (int i = 0; i < padding; i++)
            ft_putchar(' ', length, flag);
    }
}


/* %p The void pointer * given as argument is printed in hexadecimal format. */
void ft_pointer(uintptr_t pointer, int *length, int *flag, ft_printf *ft_flags)
{
    char	str_hex[17];
    int		i;
    char	*hex = "0123456789abcdef";

    if (pointer == 0)
    {
        if (write(1, "(nil)", 5) == -1)
        {
            (*flag) = -1;
            return ;
        }
        (*length) += 5;
        return ;
    }

    // Escribir "0x" como prefijo
    if (write(1, "0x", 2) == -1)
    {
        (*flag) = -1;
        return ;
    }
    (*length) += 2;

    i = 0;
    while (pointer != 0)
    {
        str_hex[i] = hex[pointer % 16];
        pointer = pointer / 16;
        i++;
    }
    
    while (i--)
        ft_putchar(str_hex[i], length, flag);
}


/* %x Prints a hexadecimal number (base 16) in lower case.
%X Prints a hexadecimal number (base 16) in uppercase. */
void	ft_hex(unsigned int nbr, int *length, char x, int *flag)
{
	char	str_hex[17];
	char	*hex;
	int		i;

	if (x == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	i = 0;
	if (nbr == 0)
	{
		ft_putchar('0', length, flag);
		return ;
	}
	while (nbr != 0)
	{
		str_hex[i] = hex[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i--)
		ft_putchar(str_hex[i], length, flag);
}
