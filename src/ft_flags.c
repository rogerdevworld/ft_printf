
//ft_flags 
#include "libftprintf.h"

void    is_flag(char c, va_list args, int *length, int *i)
{
    if (c == 'c')
        ft_putchar(va_args(args, char *), length);
    else if (c == 's')
        ft_putstr(va_args(args, int), length);
    else if (c == 'p')
        ft_pointer(va_args(args, size_t), length);
    else if (c == 'u')
        ft_unsigned_putnbr(va_args(args, unsigned int), length);
    else if (c == 'd' || c == 'i')
        ft_putnbr(va_args(args, int), length);
    else if (c == 'x')
        ft_putstr(va_args(args, unsigned int), length, 'x');
    else if (c == 'X')
        ft_putstr(va_args(args, unsigned int), length, 'X'); 
    else if (c == '%')
        ft_putchar('%', length);
    else
        (*i)--;
}

/* • %u Imprime un número decimal (base 10) sin signo. */
void	ft_unsigned_putnbr(unsigned int u, int *length)
{
	if (u > 9)
		ft_unsigned_int(u / 10, length);
	ft_putcharacter_length(u % 10 + '0', length);
}