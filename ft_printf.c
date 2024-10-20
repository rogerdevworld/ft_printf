#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* print char*/
void ft_putchar(const char c)
{
  write(1, &c, 1);
}

/* print functions*/
void ft_putstr(const char *str)
{
  int ch;

  ch = 0;
  while (str[ch])
  {
    ft_putchar(str[ch]);
    ch++;
  } 
}

/* get len of string */
int ft_strlen(const char *str)
{
  int length;
  
  length = 0;
  while (str[length])
    length++;
  return (length);
}

/* detector de flags si es -1 el return retornamos error */
int is_flag(char c)
{
    return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X');
}

/* args counter */
int ft_size_args(const char *str)
{
    size_t length;
    int j;

    length = 0;
    j = 0;
    while (str[j])
    {
        if (str[j] == '%')
        {
            if (str[j + 1] == '%')
            {
                j++;
            }
            else if (is_flag(str[j + 1]))
            {
                length++;
                j++;
            }
            else
            {
                return -1;
            }
        }
        j++;
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

void ft_main_funtions_printf(const char *str, ...)
{
  int j;
  int length;
  int count_args = ft_size_args(str);
  va_list flags;
  va_start(flags, str);

  j = 0;
  length = 0;
  while (str[j])
  {
    if (str[j] == '%')
    {
      if (str[j + 1] == 's' )
      {
        ft_putstr(va_arg(flags, char *));
        length--;
      }
      else if (str[j + 1] == 'c')
      {
        ft_putchar((char) va_arg(flags, int));
        length--;
      }
      else if (str[j + 1] == '%')
      {
        ft_putstr("%%");
        j++;
        length++;
      }
    }
    length++;
    ft_putchar(str[j]);
    j++;
  }
  va_end(flags);
}
/* dejare el ft_printf para manejo de errores etc y llamar a las funciones finales */
int ft_printf(const char *str, ...)
{
  int i;

  i = 0;
  /* valorando ft_size_args aqui ya no necesito evaluar en ft_main */
  if (!*str || ft_size_args(str) == -1)
    return (0);




  return (i);

}

/* tester de la funcion ft_main */
int main(void) {
    int count = 0;

    ft_main_funtions_printf("Hello %s, your grade is %c. Here is 100%% correct!\n", "Alice", 'A');
    printf("Total characters processed (without counting flags): %d\n", count);

    return 0;
}


























































































/*

// test de int ft_size_args(const char *str, int *i);

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