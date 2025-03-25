#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_printf
{
    int width;
    int accuracy;
    int zero;
    int dot;
    int dash;
    int total_length;
    int sign;
    int is_zero;
    int percent;
    int space;
    int hash;
} t_printf;

/* Main function */
int ft_printf(const char *str, ...);

/* Initialization */
void ft_initialise_flags(t_printf *ft_flags);

/* Flag handlers */
void handle_char(t_printf *ft_flags, va_list args, int *length);
void handle_string(t_printf *ft_flags, va_list args, int *length);
void handle_integer(t_printf *ft_flags, va_list args, int *length);
void handle_pointer(t_printf *ft_flags, va_list args, int *length);
void handle_hex(t_printf *ft_flags, va_list args, int *length, char spec);
void handle_unsigned(t_printf *ft_flags, va_list args, int *length);
void handle_percent(t_printf *ft_flags, int *length);

/* Utils */
void ft_putstr(char *str, int *length);
void ft_putchar(char c, int *length);
int ft_isdigit(int c);
size_t ft_strlen(const char *s);
int ft_numlen(long num);
void ft_putnbr(long n, int *length);
int ft_numlen_base(unsigned long num, int base);
void ft_putnbr_base(unsigned long n, int base, int uppercase, int *length);

#endif