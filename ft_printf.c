#include "libftprintf.h"

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
    return (-1);
  while (str[i])
  {
    if (str[i] == '%')
    {
      i++;
      if (str[i])
        is_flag(str[i], args, &length, &i);
    else 
      ft_putchar(str[i], &length);
    i++;
  }
  va_end(args);
  return (length);
}