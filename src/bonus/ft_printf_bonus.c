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
#include "../../include/ft_printf_bonus.h"

// Función principal ft_printf
int ft_printf(const char *str, ...)
{
    va_list args;
    va_start(args, str);

    t_printf *ft_flags = malloc(sizeof(t_printf));
	if (!ft_flags)
		return (NULL);
    int total_printed = 0;  // Contador de caracteres impresos
    while (*str)
    {
        if (*str == '%')  // Si encontramos un '%' en el stro
        {
            str++;  // Saltamos el '%'
            ft_initialise_flags(&ft_flags);  // Inicializamos los flags

            // Leer los flags (como '-', '0', '#', ' ', '+')
            while (*str == '-' || *str == '0' || *str == '#' || *str == ' ' || *str == '+')
            {
                if (*str == '-')
                    ft_flags.dash = 1;
                else if (*str == '0')
                    ft_flags.zero = 1;
                else if (*str == '#')
                    ft_flags.hash = 1;
                else if (*str == ' ')
                    ft_flags.space = 1;
                else if (*str == '+')
                    ft_flags.sign = 1;
                str++;
            }

            // Leer el ancho (width)
            while (*str >= '0' && *str <= '9')
            {
                ft_flags.width = ft_flags.width * 10 + (*str - '0');
                str++;
            }

            // Leer la precisión (si está presente)
            if (*str == '.')
            {
                ft_flags.dot = 1;
                str++;
                ft_flags.accuracy = 0;
                while (*str >= '0' && *str <= '9')
                {
                    ft_flags.accuracy = ft_flags.accuracy * 10 + (*str - '0');
                    str++;
                }
            }

            // Validar el especificador con la función ft_validation
            if (ft_validation(*str) == 1)
            {
                // Llamar a la función correspondiente según el tipo de especificador
                if (*str == 'c')
                    handle_char(&ft_flags, args);
                else if (*str == 's')
                    handle_string(&ft_flags, args);
                else if (*str == 'd' || *str == 'i' || *str == 'u')
                    handle_integer(&ft_flags, args);
                else if (*str == '%')
                    handle_char(&ft_flags, args);  // Para manejar el '%' como un carácter literal
                total_printed += ft_flags.width;  // Incrementar el contador de caracteres impresos
            }
            else
            {
                // Si el especificador no es válido, solo lo imprimimos
                write(1, str - 1, 1);
                total_printed++;
            }
        }
        else
        {
            // Imprimir caracteres normales fuera de los especificadores
            write(1, str, 1);
            total_printed++;
        }
        str++;
    }

    va_end(args);
    return total_printed;  // Retornar el total de caracteres impresos
}
