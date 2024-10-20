#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* print char*/
void putchar(char c)
{
  write(1, &c, 1);
}

/* print functions*/
int putstr(char *str, int *i)
{
  while (*str)
  {
    write(1, str++, 1);
    i++;
  }
}

/* detector de flags si es -1 el return retornamos error */
int is_flag(char c)
{
    return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X');
}
/* args counter */
int ft_size_args(const char *str, int *i)
{
    size_t length;

    length = 0;
    while (str[i])
    {
        if (str[i] == '%')
        {
            if (str[i + 1] == '%')
            {
                i++;
            }
            else if (is_flag(str[i + 1]))
            {
                length++;
                i++;
            }
            else
            {
                return -1;
            }
        }
        i++;
    }
    return length;
}
/* tengo que llamar a 9 funciones de momento 

• %c Imprime un solo carácter.
• %s Imprime una string (como se define por defecto en C).
• %p El puntero void * dado como argumento se imprime en formato hexadecimal.
• %d Imprime un número decimal (base 10).
• %i Imprime un entero en base 10.
• %u Imprime un número decimal (base 10) sin signo.
• %x Imprime un número hexadecimal (base 16) en minúsculas.
• %X Imprime un número hexadecimal (base 16) en mayúsculas.
• % % para imprimir el símbolo del porcentaje.

*/
/* primero tomare los casos de c y s que son los mas faciles */

void ft_main_funtions_printf(const char *str, int *i, ...)
{
  int j;
  va_list flags;
  va_start(flags, ft_size_args(*str));

  j = 0;
  while (j > )

  va_end(flags);
}
/* dejare el ft_printf para manejo de errores etc y llamar a las funciones finales */
int ft_printf(const char *str, ...)
{
  int i;

  i = 0;
  if (!*str || ft_size_args(*str) == -1)
    return (NULL);




  return (i);

}




























































































/*
int main(void)
{
    printf("%d\n", ft_size_args("%c")); // Debería devolver 1
    printf("%d\n", ft_size_args("Hello %s, you have %d new messages.")); // Debería devolver 2
    printf("%d\n", ft_size_args("No flags here.")); // Debería devolver 0
    printf("%d\n", ft_size_args("%%")); // Debería devolver 0
    printf("%d\n", ft_size_args("This % is invalid.")); // Debería devolver -1
    printf("%d\n", ft_size_args("Here is one flag: %d and another %%.")); // Debería devolver 1
    printf("%d\n", ft_size_args("Only %% valid.")); // Debería devolver 0

    return 0;
}*/