/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:36:29 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/21 17:48:51 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/libftprintf.h"

/* bateria de tester */
int main(void)
{
    char c = 'A';
    char *str = "Hello, World!";
    void *ptr = &c;
    int decimal = 42;
    int integer = -42;
    unsigned int u_decimal = 123456789;
    unsigned int hex = 0x2A;
    unsigned int hex_upper = 0x2A;
 
    ft_printf("Character: %c\n", c);
    ft_printf("String: %s\n", str);
    ft_printf("Pointer: %p\n", ptr);
    ft_printf("Decimal (%%d): %d\n", decimal);
    ft_printf("Integer (%%i): %i\n", integer);
    ft_printf("Unsigned decimal (%%u): %u\n", u_decimal);
    ft_printf("Hexadecimal (%%x): %x\n", hex);
    ft_printf("Hexadecimal (%%X): %X\n", hex_upper);
    ft_printf("Percentage: %%\n");

    return 0;
}
