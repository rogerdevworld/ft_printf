#include "../../include/ft_printf_bonus.h"

void ft_initialise_flags(t_printf *ft_flags)
{
    ft_flags->width = 0;
    ft_flags->accuracy = -1;
    ft_flags->zero = 0;
    ft_flags->dot = 0;
    ft_flags->dash = 0;
    ft_flags->total_length = 0;
    ft_flags->sign = 0;
    ft_flags->is_zero = 0;
    ft_flags->percent = 0;
    ft_flags->space = 0;
    ft_flags->hash = 0;
}

static void parse_flags(const char **str, t_printf *ft_flags)
{
    while (**str == '-' || **str == '0' || **str == '#' || 
           **str == ' ' || **str == '+')
    {
        if (**str == '-')
            ft_flags->dash = 1;
        else if (**str == '0')
            ft_flags->zero = 1;
        else if (**str == '#')
            ft_flags->hash = 1;
        else if (**str == ' ')
            ft_flags->space = 1;
        else if (**str == '+')
            ft_flags->sign = 1;
        (*str)++;
    }
}

static void parse_width(const char **str, t_printf *ft_flags)
{
    while (ft_isdigit(**str))
    {
        ft_flags->width = ft_flags->width * 10 + (**str - '0');
        (*str)++;
    }
}

static void parse_precision(const char **str, t_printf *ft_flags)
{
    if (**str == '.')
    {
        ft_flags->dot = 1;
        (*str)++;
        ft_flags->accuracy = 0;
        while (ft_isdigit(**str))
        {
            ft_flags->accuracy = ft_flags->accuracy * 10 + (**str - '0');
            (*str)++;
        }
    }
}

static int is_valid_specifier(char c)
{
    return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||
            c == 'u' || c == 'x' || c == 'X' || c == '%');
}

int ft_printf(const char *str, ...)
{
    va_list args;
    t_printf ft_flags;
    int length = 0;

    va_start(args, str);
    while (*str)
    {
        if (*str == '%')
        {
            str++;
            ft_initialise_flags(&ft_flags);
            parse_flags(&str, &ft_flags);
            parse_width(&str, &ft_flags);
            parse_precision(&str, &ft_flags);
            
            if (is_valid_specifier(*str))
            {
                if (*str == 'c')
                    handle_char(&ft_flags, args, &length);
                else if (*str == 's')
                    handle_string(&ft_flags, args, &length);
                else if (*str == 'd' || *str == 'i')
                    handle_integer(&ft_flags, args, &length);
                else if (*str == 'u')
                    handle_unsigned(&ft_flags, args, &length);
                else if (*str == 'p')
                    handle_pointer(&ft_flags, args, &length);
                else if (*str == 'x' || *str == 'X')
                    handle_hex(&ft_flags, args, &length, *str);
                else if (*str == '%')
                    handle_percent(&ft_flags, &length);
                str++;
            }
        }
        else
            ft_putchar(*str++, &length);
    }
    va_end(args);
    return (length);
}

void handle_char(t_printf *ft_flags, va_list args, int *length)
{
    char c = (char)va_arg(args, int);
    int padding = ft_flags->width - 1;

    if (ft_flags->dash)
    {
        ft_putchar(c, length);
        while (padding-- > 0)
            ft_putchar(' ', length);
    }
    else
    {
        while (padding-- > 0)
            ft_putchar(ft_flags->zero ? '0' : ' ', length);
        ft_putchar(c, length);
    }
}

void handle_string(t_printf *ft_flags, va_list args, int *length)
{
    char *str = va_arg(args, char *);
    int len;
    int padding;

    if (!str)
        str = "(null)";
    
    len = ft_strlen(str);
    // Precisión limita la longitud máxima a imprimir
    if (ft_flags->dot && ft_flags->accuracy < len)
        len = ft_flags->accuracy;
    
    padding = ft_flags->width - len;
    
    // Imprimir padding izquierdo (solo si no hay alineación izquierda)
    if (!ft_flags->dash && padding > 0)
        while (padding-- > 0)
            ft_putchar(' ', length);
    
    // Imprimir el string (hasta la longitud determinada)
    write(1, str, len);
    (*length) += len;
    
    // Imprimir padding derecho (para alineación izquierda)
    if (ft_flags->dash && padding > 0)
        while (padding-- > 0)
            ft_putchar(' ', length);
}

void handle_integer(t_printf *ft_flags, va_list args, int *length)
{
    long num = va_arg(args, int);
    int is_negative = num < 0;
    unsigned long abs_num = is_negative ? -num : num;
    int num_len = ft_numlen_base(abs_num, 10);
    int zeros = 0;
    int padding;
    int total_len;

    // Calcular ceros por precisión
    if (ft_flags->dot)
    {
        zeros = ft_flags->accuracy - num_len;
        if (zeros < 0)
            zeros = 0;
        // El flag '0' se ignora cuando hay precisión
        ft_flags->zero = 0;
    }

    total_len = num_len + zeros;
    if (is_negative || ft_flags->sign || ft_flags->space)
        total_len++;

    // Calcular padding (solo espacios, los ceros ya se contaron en 'zeros')
    padding = ft_flags->width - total_len;

    // Caso especial: cero con precisión 0
    if (abs_num == 0 && ft_flags->dot && ft_flags->accuracy == 0)
    {
        // Solo imprimir el padding y el signo si es necesario
        if (is_negative || ft_flags->sign || ft_flags->space)
        {
            if (is_negative)
                ft_putchar('-', length);
            else if (ft_flags->sign)
                ft_putchar('+', length);
            else if (ft_flags->space)
                ft_putchar(' ', length);
            padding--;
        }
        while (padding-- > 0)
            ft_putchar(' ', length);
        return;
    }

    // Imprimir padding izquierdo (solo espacios)
    if (!ft_flags->dash && padding > 0)
    {
        while (padding-- > 0)
            ft_putchar(' ', length);
    }

    // Imprimir signo
    if (is_negative)
        ft_putchar('-', length);
    else if (ft_flags->sign)
        ft_putchar('+', length);
    else if (ft_flags->space)
        ft_putchar(' ', length);

    // Imprimir ceros por precisión
    while (zeros-- > 0)
        ft_putchar('0', length);

    // Imprimir el número (si no es cero o precisión no es cero)
    if (abs_num != 0 || !ft_flags->dot || ft_flags->accuracy != 0)
        ft_putnbr_base(abs_num, 10, 0, length);

    // Imprimir padding derecho
    if (ft_flags->dash && padding > 0)
        while (padding-- > 0)
            ft_putchar(' ', length);
}

void ft_putnbr_base(unsigned long n, int base, int uppercase, int *length)
{
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    
    if (n >= (unsigned long)base)
        ft_putnbr_base(n / base, base, uppercase, length);
    ft_putchar(digits[n % base], length);
}

void handle_unsigned(t_printf *ft_flags, va_list args, int *length)
{
    unsigned long num = va_arg(args, unsigned int);
    int num_len = ft_numlen_base(num, 10);
    int zeros = 0;
    int padding;

    // Calcular ceros por precisión
    if (ft_flags->dot)
    {
        zeros = ft_flags->accuracy - num_len;
        if (zeros < 0)
            zeros = 0;
        // El flag '0' se ignora cuando hay precisión
        ft_flags->zero = 0;
    }

    // Calcular padding (solo espacios)
    padding = ft_flags->width - num_len - zeros;

    // Caso especial: cero con precisión 0
    if (num == 0 && ft_flags->dot && ft_flags->accuracy == 0)
    {
        while (padding-- > 0)
            ft_putchar(' ', length);
        return;
    }

    // Imprimir padding izquierdo
    if (!ft_flags->dash && padding > 0)
    {
        while (padding-- > 0)
            ft_putchar(' ', length);
    }

    // Imprimir ceros por precisión
    while (zeros-- > 0)
        ft_putchar('0', length);

    // Imprimir el número
    if (num != 0 || !ft_flags->dot || ft_flags->accuracy != 0)
        ft_putnbr_base(num, 10, 0, length);

    // Imprimir padding derecho
    if (ft_flags->dash && padding > 0)
        while (padding-- > 0)
            ft_putchar(' ', length);
}

void handle_pointer(t_printf *ft_flags, va_list args, int *length)
{
    uintptr_t ptr = va_arg(args, uintptr_t);
    char buffer[20];
    int i = 0;
    int padding;

    if (!ptr)
    {
        ft_putstr("0x0", length);
        return;
    }

    ft_putstr("0x", length);
    while (ptr)
    {
        buffer[i++] = "0123456789abcdef"[ptr % 16];
        ptr /= 16;
    }
    padding = ft_flags->width - (i + 2);
    
    if (!ft_flags->dash && padding > 0)
        while (padding-- > 0)
            ft_putchar(' ', length);
    
    while (i-- > 0)
        ft_putchar(buffer[i], length);
    
    if (ft_flags->dash && padding > 0)
        while (padding-- > 0)
            ft_putchar(' ', length);
}

void handle_hex(t_printf *ft_flags, va_list args, int *length, char spec)
{
    unsigned int num = va_arg(args, unsigned int);
    int num_len = ft_numlen_base(num, 16);
    int zeros = 0;
    int padding;
    int prefix_len = 0;

    // Calcular ceros por precisión
    if (ft_flags->dot)
    {
        zeros = ft_flags->accuracy - num_len;
        if (zeros < 0)
            zeros = 0;
        // El flag '0' se ignora cuando hay precisión
        ft_flags->zero = 0;
    }

    // Calcular longitud del prefijo
    if (ft_flags->hash && num != 0)
        prefix_len = 2;

    // Calcular padding (solo espacios)
    padding = ft_flags->width - num_len - zeros - prefix_len;

    // Caso especial: cero con precisión 0
    if (num == 0 && ft_flags->dot && ft_flags->accuracy == 0)
    {
        while (padding-- > 0)
            ft_putchar(' ', length);
        return;
    }

    // Imprimir padding izquierdo
    if (!ft_flags->dash && padding > 0)
    {
        while (padding-- > 0)
            ft_putchar(' ', length);
    }

    // Imprimir prefijo
    if (ft_flags->hash && num != 0)
    {
        ft_putchar('0', length);
        ft_putchar(spec, length);
    }

    // Imprimir ceros por precisión
    while (zeros-- > 0)
        ft_putchar('0', length);

    // Imprimir el número
    if (num != 0 || !ft_flags->dot || ft_flags->accuracy != 0)
        ft_putnbr_base(num, 16, (spec == 'X'), length);

    // Imprimir padding derecho
    if (ft_flags->dash && padding > 0)
        while (padding-- > 0)
            ft_putchar(' ', length);
}

int ft_numlen_base(unsigned long num, int base)
{
    int len = 0;

    if (num == 0)
        return 1;
    
    while (num)
    {
        len++;
        num /= base;
    }
    return len;
}

void handle_percent(t_printf *ft_flags, int *length)
{
    int padding = ft_flags->width - 1;

    if (!ft_flags->dash && padding > 0)
    {
        while (padding-- > 0)
            ft_putchar(ft_flags->zero ? '0' : ' ', length);
    }

    ft_putchar('%', length);

    if (ft_flags->dash && padding > 0)
        while (padding-- > 0)
            ft_putchar(' ', length);
}

void ft_putchar(char c, int *length)
{
    write(1, &c, 1);
    (*length)++;
}

void ft_putstr(char *str, int *length)
{
    if (!str)
        return;
        
    while (*str)
        ft_putchar(*str++, length);
}

int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

int ft_numlen(long num)
{
    int len = 0;

    if (num == 0)
        return 1;
    
    if (num < 0)
    {
        len++;
        num = -num;
    }

    while (num)
    {
        len++;
        num /= 10;
    }
    return len;
}

void ft_putnbr(long n, int *length)
{
    if (n < 0)
    {
        ft_putchar('-', length);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr(n / 10, length);
    ft_putchar(n % 10 + '0', length);
}

