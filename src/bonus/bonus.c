#include "../../include/ft_printf_bonus.h"

/* struct bonus initialization */
t_printf *ft_initialise_flags(t_printf *ft_flags)                       
{                    
      ft_flags->width = 0;     
      ft_flags->accuracy = -1;                        
      ft_flags->zero = 0;                        
      ft_flags->dot = 0;                        
      ft_flags->dash = 0;                        
      ft_flags->total_lenght = 0;                        
      ft_flags->sign = 0;                        
      ft_flags->is_zero = 0;                        
      ft_flags->percen = 0;                        
      ft_flags->space = 0;                        
      return (ft_flags);                       
}

void parse_str(const char *str, t_printf *ft_flags)
{
    // Inicializar los flags antes de procesar el stro
    ft_initialise_flags(ft_flags);

    // Leer los flags
    while (*str == '-' || *str == '0' || *str == '#' || *str == ' ' || *str == '+')
    {
        if (*str == '-')
            ft_flags->dash = 1;
        else if (*str == '0')
            ft_flags->zero = 1;
        else if (*str == '#')
            ft_flags->hash = 1;
        else if (*str == ' ')
            ft_flags->space = 1;
        else if (*str == '+')
            ft_flags->sign = 1;

        str++;
    }

    // Leer el ancho (width)
    while (ft_isdigit(*str))
    {
        ft_flags->width = ft_flags->width * 10 + (*str - '0');
        str++;
    }

    // Leer la precisión (si está presente)
    if (*str == '.')
    {
        ft_flags->dot = 1;
        str++; // Saltar el punto '.'
        ft_flags->accuracy = 0;
        while (ft_isdigit(*str))
        {
            ft_flags->accuracy = ft_flags->accuracy * 10 + (*str - '0');
            str++;
        }
    }

    // Asignar el especificador de stro
    if (*str == 'c' || *str == 's' || *str == 'p' || *str == 'd' || *str == 'i' ||
        *str == 'u' || *str == 'x' || *str == 'X' || *str == '%')
    {
        // Guardar el especificador
        ft_flags->percent = (*str == '%');
    }
}

void apply_format(t_printf *ft_flags, va_list args)
{
    int num_len = 0;
    int num = 0;
    double float_num = 0.0;

    // Determinar si el número es entero o flotante
    if (ft_flags->percent) {
        // Caso específico para porcentaje
        num_len = 1;  // Un solo carácter '%'
    }
    else if (*format == 'd' || *format == 'i' || *format == 'u') {
        num = va_arg(args, int);
        num_len = num_len(num);  // Calculamos la longitud del número entero
    }
    else if (*format == 'f') {
        float_num = va_arg(args, double);
        num_len = float_len(float_num, ft_flags->accuracy);  // Calculamos la longitud de un número flotante
    }

    // Verificamos si el número necesita ser rellenado
    if (ft_flags->width > num_len)
    {
        // Rellenar con espacios o ceros (dependiendo del flag '0' o 'dash')
        int padding = ft_flags->width - num_len;
        if (ft_flags->dash) {
            // Imprimir el número primero (alineado a la izquierda)
            printf("%d", num);  // Imprime el número
            for (int i = 0; i < padding; i++)
                putchar(' ');  // Rellenar con espacios
        }
        else {
            // Imprimir primero los espacios o ceros
            if (ft_flags->zero) {
                for (int i = 0; i < padding; i++)
                    putchar('0');  // Rellenar con ceros
            } else {
                for (int i = 0; i < padding; i++)
                    putchar(' ');  // Rellenar con espacios
            }
            printf("%d", num);  // Imprimir el número
        }
    } else {
        // Si el número tiene suficiente longitud, se imprime normalmente
        printf("%d", num);
    }
}

int num_len(int num)
{
    int len = 0;

    // Si el número es cero, tiene una longitud de 1
    if (num == 0)
        return 1;

    // Si el número es negativo, contarlo como un dígito extra para el signo
    if (num < 0)
    {
        len++; // Cuenta el signo '-'
        num = -num; // Convertir el número a positivo para facilitar el conteo
    }

    // Contar la cantidad de dígitos del número
    while (num > 0)
    {
        len++;
        num /= 10;
    }

    return len;
}


int float_len(double num, int precision)
{
    int len = 0;

    // Si el número es cero, tiene una longitud de 1
    if (num == 0.0)
        return 1;

    // Contar la parte entera
    if (num < 0)
    {
        len++; // Cuenta el signo '-'
        num = -num; // Convertir el número a positivo
    }

    // Parte entera del número
    int integer_part = (int)num;
    len += num_len(integer_part);  // Usamos la función para calcular la longitud de la parte entera

    // Contar la parte decimal, si es necesario
    if (precision > 0)
    {
        len++;  // Contamos el punto decimal '.'
        num -= integer_part; // Eliminar la parte entera
        for (int i = 0; i < precision; i++)
        {
            num *= 10;  // Desplazar la parte decimal
            int digit = (int)num;
            len++; // Contamos cada dígito
            num -= digit; // Eliminar el dígito que acabamos de contar
        }
    }

    return len;
}

void handle_char(t_printf *fmt, va_list args)
{
    char c = (char)va_arg(args, int);  // Obtener el argumento de tipo char

    // Calcular el padding necesario (si hay un ancho mínimo)
    int len = 1;  // Un carácter tiene longitud 1
    int padding = fmt->width - len;

    if (fmt->dash) {
        // Si la bandera '-' está activa, imprimir el carácter primero (alineado a la izquierda)
        putchar(c);
        for (int i = 0; i < padding; i++) {
            putchar(' ');  // Rellenar con espacios a la derecha
        }
    } else {
        // Si no hay bandera '-', rellenar con espacios o ceros a la izquierda
        if (fmt->zero) {
            for (int i = 0; i < padding; i++) {
                putchar('0');  // Rellenar con ceros
            }
        } else {
            for (int i = 0; i < padding; i++) {
                putchar(' ');  // Rellenar con espacios
            }
        }
        putchar(c);  // Imprimir el carácter
    }
}

void handle_string(t_printf *fmt, va_list args)
{
    char *str = va_arg(args, char *);  // Obtener el argumento de tipo cadena
    if (str == NULL) {
        str = "(null)";  // Manejo del caso de cadena nula
    }

    // Calcular la longitud de la cadena
    int len = strlen(str);

    // Si se especifica una precisión, truncar la cadena
    if (fmt->accuracy >= 0 && fmt->accuracy < len) {
        len = fmt->accuracy;
    }

    // Calcular el padding necesario (si hay un ancho mínimo)
    int padding = fmt->width - len;

    if (fmt->dash) {
        // Si la bandera '-' está activa, imprimir la cadena primero (alineada a la izquierda)
        for (int i = 0; i < len; i++) {
            putchar(str[i]);  // Imprimir cada carácter de la cadena
        }
        for (int i = 0; i < padding; i++) {
            putchar(' ');  // Rellenar con espacios a la derecha
        }
    } else {
        // Si no hay bandera '-', rellenar con espacios o ceros a la izquierda
        if (fmt->zero) {
            for (int i = 0; i < padding; i++) {
                putchar('0');  // Rellenar con ceros
            }
        } else {
            for (int i = 0; i < padding; i++) {
                putchar(' ');  // Rellenar con espacios
            }
        }
        for (int i = 0; i < len; i++) {
            putchar(str[i]);  // Imprimir cada carácter de la cadena
        }
    }
}

void handle_integer(t_printf *fmt, va_list args)
{
    int num = va_arg(args, int);  // Obtener el argumento de tipo entero
    int is_negative = num < 0;  // Verificar si el número es negativo
    unsigned int abs_num = (is_negative) ? -num : num;  // Tomar el valor absoluto si es negativo

    // Calcular la longitud del número
    int len = 0;
    unsigned int temp_num = abs_num;
    if (temp_num == 0) {
        len = 1;  // El número cero tiene longitud 1
    } else {
        while (temp_num > 0) {
            len++;
            temp_num /= 10;
        }
    }

    // Si el número es negativo, contar el signo '-'
    if (is_negative) {
        len++;
    }

    // Calcular el padding necesario (si hay un ancho mínimo)
    int padding = fmt->width - len;

    if (fmt->dash) {
        // Si la bandera '-' está activa, imprimir el número primero (alineado a la izquierda)
        if (is_negative) {
            putchar('-');  // Imprimir el signo '-'
        }
        printf("%u", abs_num);  // Imprimir el número sin signo
        for (int i = 0; i < padding; i++) {
            putchar(' ');  // Rellenar con espacios a la derecha
        }
    } else {
        // Si no hay bandera '-', rellenar con espacios o ceros a la izquierda
        if (fmt->zero) {
            if (is_negative) {
                putchar('-');  // Imprimir el signo '-' antes de los ceros
            }
            for (int i = 0; i < padding; i++) {
                putchar('0');  // Rellenar con ceros
            }
        } else {
            for (int i = 0; i < padding; i++) {
                putchar(' ');  // Rellenar con espacios
            }
            if (is_negative) {
                putchar('-');  // Imprimir el signo '-'
            }
        }
        printf("%u", abs_num);  // Imprimir el número sin signo
    }
}
