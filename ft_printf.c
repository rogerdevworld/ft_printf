#include "libftprintf.h"
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>

/* • %c Imprime un solo carácter. */
void	ft_putchar(char character, int *length){
	write(1, &character, 1);
	(*length)++;
}

/* • %s Imprime una string (como se define por defecto en C) */
void	ft_putstr(char *args, int *length)
{
	size_t	i;

	i = 0;
	if (!args)
	{
		write(1, "(null)", 6);
		(*length) += 6;
		return ;
	}
	while (args[i])
	{
		ft_putchar(args[i], length);
		i++;
	}
}

/* 
• %d Imprime un número decimal (base 10).
• %i Imprime un entero en base 10.
*/
void	ft_putnbr(int nbr, int *length)
{
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*length) += 11;
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar('-', length);
		ft_putnbr(nbr * -1, length);
	}
	else
	{
		if (nbr > 9)
			ft_putnbr(nbr / 10, length);
		ft_putchar(nbr % 10 + '0', length);
	}
}

/* • %p El puntero void * dado como argumento se imprime en formato hexadecimal. */
void	ft_pointer(uintptr_t pointer, int *length)
{
	char	str_hex[25];
	int		i;
	char	*hex;

	hex = "0123456789abcdef";
	i = 0;
	write(1, "0x", 2);
	(*length) += 2;
	if (pointer == 0)
	{
		ft_putchar('0', length);
		return ;
	}
	while (pointer != 0)
	{
		str_hex[i] = hex[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
		ft_putchar(str_hex[i], length);
}

/* • %x Imprime un número hexadecimal (base 16) en minúsculas.
• %X Imprime un número hexadecimal (base 16) en mayúsculas. */
void	ft_hex(unsigned int nbr, int *length, char x)
{
	char	str_hex[25];
	char	*hex;
	int		i;

	if (x == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	i = 0;
	if (nbr == 0)
	{
		ft_putchar('0', length);
		return ;
	}
	while (nbr != 0)
	{
		str_hex[i] = hex [nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i--)
		ft_putchar(str_hex[i], length);
}

/* • %u Imprime un número decimal (base 10) sin signo. */
void	ft_unsigned_putnbr(unsigned int u, int *length)
{
	if (u > 9)
		ft_unsigned_putnbr(u / 10, length);
	ft_putchar(u % 10 + '0', length);
}

/* cazador de flgas */
void    is_flag(char c, va_list args, int *length, int *i)
{
    if (c == 'c')
        ft_putchar((char)va_arg(args, int), length);
    else if (c == 's')
        ft_putstr(va_arg(args, char *), length);
    else if (c == 'p')
        ft_pointer(va_arg(args, uintptr_t), length);
    else if (c == 'u')
        ft_unsigned_putnbr(va_arg(args, unsigned int), length);
    else if (c == 'd' || c == 'i')
        ft_putnbr(va_arg(args, int), length);
    else if (c == 'x')
        ft_hex(va_arg(args, unsigned int), length, 'x');
    else if (c == 'X')
        ft_hex(va_arg(args, unsigned int), length, 'X'); 
    else if (c == '%')
        ft_putchar('%', length);
    else
        (*i)--;
}

/* dejare el ft_printf para manejo de errores etc y llamar a las funciones finales */
int ft_printf(const char *str, ...)
{
  int i;
  int length;
  va_list args;

  i = 0;
  length = 0;
  va_start(args, str);
  if (!*str)
    return (0);
  while (str[i])
  {
    if (str[i] == '%')
    {
      i++;
      if (str[i])
        is_flag(str[i], args, &length, &i);
      else
        break ;
    }
    else 
      ft_putchar(str[i], &length);
    i++;
  }
  va_end(args);
  return (length);
}
