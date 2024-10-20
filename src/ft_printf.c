#include "../include/libftprintf.h"

/* dejare el ft_printf para manejo de errores etc y llamar a las funciones finales */
int ft_printf(const char *str, ...)
{
  int i;
  int length;

  i = 0;
  if (!*str || ft_size_args(str) == -1)
    return (0);
  while (str[i])
  {
    if (str[i++] == '%')
      is_flag(str[i], args, &length, &i);
    else 
      ft_putchar(str[i], &length);
    i++;
  }
  va_end(args);
  return (length);
}