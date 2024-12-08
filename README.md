# Primero paso en `ft_printf`:

```c
//prototipo de la funcion ft_printf();
int ft_printf(char const, ...);
```

Retornamos un `int` para saber si el `printf` fue realizado correctamente, sería positivo con el número de caracteres impresos o negativo.

### ¿Que son las funciones varíadicas?

Desde ya podemos ver algo nuevo en el prototipo de `ft_printf(…)`esos puntos dentro de la función significa que vamos a recibir un número indefinido de parámetros.

Lo primero estos parámetros bariátricos están el <stdarg.h>

Tenemos que usar unas macros que son `va_list`, `va_start`, `va_arg` y `va_end`:

- `va_list`: Se utiliza para declarar una variable que almacenará el estado de los argumentos.
- `va_start`: Inicializa la variable de tipo `va_list` para empezar a recorrer los argumentos.
- `va_arg`: Recupera el siguiente argumento en la lista.
- `va_end`: Limpia la lista de argumentos cuando ya no se necesitan.

Ejemplo en código:

```c
#include <stdio.h>
#include <stdarg.h>

void sumas_de_valores(int num, ...)
{
		int i;
    va_list args;
    va_start(args, num);

		i = 0;
    while (i < num) {
	    if(num[i] == '%')
		    procesarelchar(num[i + 1])
			  i++
        int valor = va_arg(args, int);
        printf("Argumento %d: %d\n", i + 1, valor);
        i++;
    }

    va_end(args);
}

int main() {
    sumas_de_valores(3, 10, 20, 30);
    return 0;
}

```

Este ejemplo sería una suma de n argumentos y retorna `va_end(args);`

Ahora tenemos que ver la manera de trabajar con más de un tipo de dato, ya que en `va_args(agrs, typeof());`, vamos a usar el % más fácil imposible, solo tenemos que recorrer el primer `arg` que sería `const char *str`.

Podemos hacer una función que detecte los caracteres % y el tipo para pasar el tipo de datos, transformar a Sting e imprimir..

Detalles a imitar:

```c
ft_printf(cosnt char string, ...)
{
	if (!sting)
		return (NULL);
}
```
Video:

https://www.youtube.com/watch?v=yPrOq2Io4D8&t=3s

```c
printf("Bienvenido %s a %d, tu fecha de nacimiento es: %d/%d/%d", Roger, 42, 18,05,2002)
```

El protagonista de la función es % así que deberíamos usar una condición que verifique lo que sigue después del %.

### es.subject.pdf
[es.subject.pdf](https://github.com/rogerdevworld/42-subjects.pdf/blob/main/ft_printf/es.subject.pdf)
| % | Carácter que implica imprimir  |
| --- | --- |
| %c  | Imprime un solo carácter.(char) |
| %s  | Imprime una string (como se define por defecto en C).(char *) |
| %p  | %p El puntero void * dado como argumento se imprime en formato hexadecimal. |
| %d  | Imprime un número decimal (base 10). |
| %i  | Imprime un entero en base 1 |
| %u  | Imprime un número decimal (base 10) sin signo. |
| %x  | Imprime un número hexadecimal (base 16) en minúsculas. |
| %X  | Imprime un número hexadecimal (base 16) en mayúsculas. |
| %%  | Para imprimir el símbolo del porcentaje. |

---
Ya teniendo esto claro, voy a explicar la construcción de la función para poder escribir todas las funciones por pantalla que se pasan por parámetros de la función.

Lo primero sería ver el `ft_printf()`;

Tenemos dos `int i` para recorrer la string principal y cuando vea un % llamar al cazador de %, ahora `int length` la tenemos para guardar la longitud de la string final y la variable de la función variadica que sería `va_lsit args`.

- Función ft_printf
    
    ```c
    #include "../include/ft_printf.h"                                                                                   
                                                                                                                          
    /* dejare el ft_printf para manejo de errores                                                                         
    etc y llamar a las funciones finales */                                                                            
    int     ft_printf(const char *str, ...)                                                                               
    {                                                                                                                     
            int             i;//recorrer el string hasta encontrar %                                                                                            
            va_list args;//lista de args                                                                                                  
            int             length;//tamano del string final                                                                                       
                                                                                                                          
            i = 0;                                                                                                        
            length = 0;                                                                                                   
            va_start(args, str);//inicializacion de va_                                                                                          
            if (!*str)//retornamos 0 si string es NULL                                                                                                    
                    return (0);                                                                                           
            while (str[i])//recorrer string                                                                                                
            {                                                                                                             
                    if (str[i] == '%')                                                                                    
                    {                                                                                                     
                            i++;                                                                                          
                            if (str[i])                                                                                   
                                    is_flag(str[i], args, &length, &i);//cazador de flags                                                   
                            else                                                                                          
                                    break ;                                                                               
                    }                                                                                                     
                    else                                                                                                  
                            ft_putchar(str[i], &length);                                                                  
                    i++;                                                                                                  
            }                                                                                                             
            va_end(args);//final de va_                                                                                                 
            return (length);// tamano final de la string                                                                                              
    } 
    ```
    

Ahora el cazador de % para ver que funciones a utilizar para cada caso y llamando cada función para imprimir:

- Código de is_flag
    
    ```c
    /* ft_flags buscara paso a paso lo que sigue el % tenemos 9 casos validos y 1 de error que seria el % solo*/
    /* c seris el carater que viene despues de %, lenght seria el tamano final a retornar del la string final, i seria el lugar a eliminar o saltar por ser o flag */
    void    is_flag(char c, va_list args, int *length, int *i)
    {
        if (c == 'c')
            ft_putchar(va_args(args, char *), length);
        else if (c == 's')
            ft_putstr(va_args(args, int), length);
        else if (c == 'p')
            ft_pointer(va_args(args, size_t), length);
        else if (c == 'u')
            ft_putstr(va_args(args, int), length);
        else if (c == 'd' || c == 'i')
            ft_putnbr(va_args(args, int), length);
        else if (c == 'x' || c == 'X')
            ft_putstr(va_args(args, int), length); 
        else if (c == '%')
            ft_putchar('%', length);
        else
            (*i)--;//en caso que no se niguno de los caso restamos en %
     }
    ```
    

## Funciones:

### Función de carácter `ft_putchar();`:

La función de `putchar` de toda la vida con un **length** que sería mi valor final  de retorno.

- Código de `ft_putchar();`
    
    ```c
    /* • %c Imprime un solo carácter. */
    void ft_putchar(const char c, int length)
    {
      write(1, &c, 1);
      (*length)++;
    }
    ```
    

### Función de String `ft_putstr();`:

La función de `putstr` de toda la vida + length

- Código de `ft_putstr();`
    
    ```c
    /* • %s Imprime una string (como se define por defecto en C) */
    void ft_putstr(char *args, int *length)
    {
      int i;
    
      i = 0;
      if (!args)
      {
        write(1, "(null)", 6)
        (*length) += 6;
        return ;
      }
      while (args[i])
        ft_putchar(args[i++], length);
    }
    ```
    

### Funcione de numérica `ft_putnbr();`:

La función de ft_putnbr(); es la misma de la piscina 

- Código de `ft_putnbr()`;
    
    ```c
    /* 
    - %d Prints a decimal number (base 10).
    - %i Prints an integer in base 10.
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
    ```
    

### Funcione de punteros `ft_pointer();`:

Aprendamos los conceptos que representan los punteros, en este caso sería su representación de explicación en memoria, ya que la tenemos que imprimir..

Deberíamos tener en claro que son espacios en memoria contigua y se representan en números hexadecimales seguidos de `0x` en caso de ser 0 imprime `(nil)`.

La función imprime un puntero `void *` en formato hexadecimal, hasta donde entiendo es `void` porque no nos importa el tipo sino la dirección en memoria. Vale, el parámetro de tipo para tratarlo de forma numérica directamente `uintptr_t`.

`uintptr_t` es un tipo de dato que nos da la ventaja de almacenar cualquier tipo de tamaño de dirección de memoria 32 y 64 bits, este dato sería como un `unsigned int` o `unsigned long` y en 64 bits sería un `unsgined long` o `unsigned long long`

- Código `ft_pointer();`
    
    ```c
    /* %p The void pointer * given as argument is printed in hexadecimal format. */
    void	ft_pointer(uintptr_t pointer, int *length)
    {
    	char	str_hex[25];
    	int		i;
    	char	*hex;
    
    	hex = "0123456789abcdef";
    	i = 0;
    	if (pointer == 0)
    	{
    		write(1, "(nil)", 5);
    		(*length) += 5;
    		return ;
    	}
    	write(1, "0x", 2);
    	(*length) += 2;
    	while (pointer != 0)
    	{
    		str_hex[i] = hex[pointer % 16];
    		pointer = pointer / 16;
    		i++;
    	}
    	while (i--)
    		ft_putchar(str_hex[i], length);
    }
    ```
    

### Funcione de hexadecimal `ft_hex();`:

Esto sería un `ft_hex();`, pero base 16. Tenemos dos casos mayúsculos y minusculas según x hex tiene una lista de hex diferente, si es 0 imprime 0 y si tiene un valor lo almacena el módulo y divide el resto hasta llagar a cero y lo guarda al revés y lo imprime al contrario para que quede todo en su lugar.

- Código de `ft_putnbr()`;
    
    ```c
    /* %x Prints a hexadecimal number (base 16) in lower case.
    %X Prints a hexadecimal number (base 16) in uppercase. */
    void	ft_hex(unsigned int nbr, int *length, char x)
    {
    	char	str_hex[25];//valor max seria 
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
    ```
    

### Funcione de unsigned `ft_unsigned_putnbr();`:

La función de ft_unsigned_putnbr(); es la misma de la piscina 

- Código de `ft_putnbr()`;
    
    ```c
    /* %u Print an unsigned decimal number (base 10). */
    void	ft_unsigned_putnbr(unsigned int unsgined_nbr, int *length)
    {
    	if (unsgined_nbr > 9)
    		ft_unsigned_putnbr(unsgined_nbr / 10, length);
    	ft_putchar(unsgined_nbr % 10 + '0', length);
    }
    ```
    

### ft_printf.h

Nada nuevo solo definir el punto `.h`

- Código `ft_print.h`
    
    ```c
    /* header printf */
    #ifndef LIBFTPRINTF_H
    #define LIBFTPRINTF_H
    
    /* lib std */
    #include <stdio.h>
    #include <unistd.h>
    #include <stdarg.h>
    
    /* main funtion*/
    int ft_printf(const char *str, ...)
    
    /* cazador de flgas */
    void    is_flag(char c, va_list args, int *length, int *i);
    
    /* • %u Imprime un número decimal (base 10) sin signo. */
    void	ft_unsigned_putnbr(unsigned int u, int *length);
    
    /* • %c Imprime un solo carácter. */
    void ft_putchar(const char c, int length);
    
    /* • %s Imprime una string (como se define por defecto en C) */
    void ft_putstr(char *args, int *length);
    
    /* 
    • %d Imprime un número decimal (base 10).
    • %i Imprime un entero en base 10.
    */
    void  ft_putnbr(int nbr, int *length);
    
    /* • %p El puntero void * dado como argumento se imprime en formato hexadecimal. */
    void  ft_pointer(size_t pointer, int *length);
    
    /* • %x Imprime un número hexadecimal (base 16) en minúsculas.
    • %X Imprime un número hexadecimal (base 16) en mayúsculas. */
    void  ft_hex(unsigned int nbr, int length, char x);
    
    #endif
    ```
    

### Makefile

El Makefile de toda la vida

- Código `Makefile`
    
    ```c
    NAME = libftprintf.a
    SRC = ./src/ft_printf.c ./src/ft_flags.c ./src/ft_printf_utils.c
    OBJS = $(SRC:.c=.o)
    HEADER = ft_printf.h
    CC = cc
    CFLAGS = -Wall -Wextra -Werror
    RM = rm -f
    AR = ar rsc
    
    all: $(NAME)
    
    $(NAME): $(OBJS)
    	ar rsc $(NAME) $(OBJS)
    	ranlib $(NAME)
    
    %.o: %.c $(HEADER) Makefile
    	$(CC) $(CFLAGS) -c $< -o $@
    
    clean:
    	$(RM) $(OBJS)
    
    fclean: clean
    	$(RM) $(NAME)
    	
    re: fclean all
    
    .PHONY : all clean fclean re
    ```
    

Corrección:printfTester(tripouille)

[GitHub - Tripouille/printfTester: Tester for the ft_printf project of 42 school](https://github.com/Tripouille/printfTester.git)

## ft_printf_bonus

En la parte bonus de tu proyecto `ft_printf`, debes manejar combinaciones adicionales de flags y especificadores, añadiendo complejidad a la implementación. Según el documento, los casos y características que debes considerar incluyen:

1. **Flags básicos**:
    - `'-'`: Justificación a la izquierda.
    - `'0'`: Relleno con ceros.
    - `'.'`: Precisión.
2. **Flags adicionales**:
    - `'#'`: Prefijo para valores en formato hexadecimal o octal.
    - `'+'`: Imprime siempre el signo de números positivos.
    - `' '`: Espacio extra antes de números positivos (si no está el flag `+`).
3. **Ancho mínimo**:
    - Debes manejar el *minimum field width*, lo que requiere calcular el espacio disponible para cada conversión dependiendo del tamaño del contenido.
4. **Compatibilidad combinada**:
    - Todas las combinaciones posibles de los flags anteriores deben funcionar bajo todas las conversiones disponibles (c, s, p, d, i, u, x, X, %).
5. **Posibles casos a evaluar**:
    - Casos donde los flags se contradicen entre sí (por ejemplo, `0` y `` juntos).
    - Casos donde la precisión y el ancho mínimo impactan en el formato final.
    - Casos donde el valor numérico o de cadena afecta a cómo se aplican los flags, especialmente:
        - Números negativos.
        - Valores nulos o cero.
        - Strings vacías o punteros nulos.
6. **Validaciones y edge cases**:
    - Asegúrate de que los flags redundantes o no válidos se ignoren correctamente.
    - Identifica las conversiones que no aceptan ciertos flags, por ejemplo, `#` no afecta a enteros decimales.

Dado que tu estructura `t_print` ya incluye muchos campos útiles, sería ideal usar cada campo para rastrear las características correspondientes de la conversión actual. Por ejemplo:

- `zero`: Indica si el flag `0` está activo.
- `dash`: Indica si el flag `` está activo.
- `wdt` y `prc`: Ayudan a manejar el ancho mínimo y la precisión.
- `sp`: Puede usarse para el flag `' '`.

Si necesitas una lista completa de casos de prueba, puedo ayudarte a construirla detallando escenarios específicos. ¿Qué parte quieres priorizar?

---

### Casos:

### **1. Flags básicos: ``, `0`, `.` (ancho mínimo y precisión)**

### a) Combinación con `%d` (números enteros, decimales):

- **Entrada**: `"%-10d"`, `42`
    - **Salida**: `"42 "` (justificado a la izquierda, ancho mínimo de 10).
- **Entrada**: `"%010d"`, `42`
    - **Salida**: `"0000000042"` (relleno con ceros, ancho mínimo de 10).
- **Entrada**: `"%10.5d"`, `42`
    - **Salida**: `" 00042"` (ancho mínimo de 10, precisión de 5).
- **Entrada**: `"%.d"`, `0`
    - **Salida**: `""` (precisión `0` elimina el `0`).

### b) Combinación con `%s` (strings):

- **Entrada**: `"%-10s"`, `"abc"`
    - **Salida**: `"abc "` (justificado a la izquierda, ancho mínimo de 10).
- **Entrada**: `"%10.2s"`, `"abc"`
    - **Salida**: `" ab"` (ancho mínimo de 10, recortado a 2 caracteres).
- **Entrada**: `"%.0s"`, `"abc"`
    - **Salida**: `""` (precisión `0` elimina la salida).

### c) Combinación con `%p` (punteros):

- **Entrada**: `"%-15p"`, `(void *)0x1234`
    - **Salida**: `"0x1234 "` (puntero con justificación a la izquierda).
- **Entrada**: `"%20p"`, `(void *)0`
    - **Salida**: `" (nil)"` (puntero nulo, ancho mínimo de 20).

### d) Combinación con `%u` (enteros sin signo):

- **Entrada**: `"%10u"`, `123`
    - **Salida**: `" 123"` (ancho mínimo de 10, sin signo).
- **Entrada**: `"%.5u"`, `123`
    - **Salida**: `"00123"` (precisión de 5).

---

### **2. Flags adicionales: `#`, `+`,  `` (espacio)**

### a) Combinación con `%x` y `%X` (hexadecimal):

- **Entrada**: `"%#x"`, `123`
    - **Salida**: `"0x7b"` (prefijo `0x` para hexadecimal).
- **Entrada**: `"%#10X"`, `123`
    - **Salida**: `" 0X7B"` (prefijo `0X`, ancho mínimo de 10).

### b) Combinación con `%d`:

- **Entrada**: `"%+d"`, `42`
    - **Salida**: `"+42"` (imprime el signo positivo).
- **Entrada**: `"% d"`, `42`
    - **Salida**: `" 42"` (espacio antes del número positivo).
- **Entrada**: `"%+d"`, `42`
    - **Salida**: `"-42"` (signo negativo siempre se imprime).

### c) Combinación con `%o` (octal):

- **Entrada**: `"%#o"`, `123`
    - **Salida**: `"0173"` (prefijo `0` para octal).

---

### **3. Combinaciones complejas de flags y anchos**

### a) Flags contradictorios:

- **Entrada**: `"%-010d"`, `42`
    - **Salida**: `"42 "` (`` anula `0`).
- **Entrada**: `"%0.5d"`, `42`
    - **Salida**: `"00042"` (precisión anula `0`).

### b) Combinaciones extremas:

- **Entrada**: `"%#10.5x"`, `123`
    - **Salida**: `" 0x0007b"` (prefijo `0x`, ancho mínimo de 10, precisión de 5).
- **Entrada**: `"%+10.5d"`, `42`
    - **Salida**: `" -00042"` (signo y precisión dentro de ancho mínimo de 10).

---

### **4. Casos especiales por conversión**

### a) `%c` (caracteres):

- **Entrada**: `"%-5c"`, `'A'`
    - **Salida**: `"A "` (justificado a la izquierda, ancho mínimo de 5).

### b) `%s` (strings con nulo):

- **Entrada**: `"%.5s"`, `NULL`
    - **Salida**: `"(null)"` (por convención de `printf`).

### c) `%p` (punteros nulos):

- **Entrada**: `"%p"`, `(void *)0`
    - **Salida**: `"(nil)"`.

### d) `%u` con cero:

- **Entrada**: `"%.0u"`, `0`
    - **Salida**: `""` (precisión 0 elimina la salida).

### e) `%x` con cero y flag `#`:

- **Entrada**: `"%#x"`, `0`
    - **Salida**: `"0"` (prefijo omitido para 0).

---

### **5. Conversiones con `%`**

- **Entrada**: `"%5%"`, `N/A`
    - **Salida**: `" %"` (ancho mínimo de 5).
- **Entrada**: `"%-5%"`, `N/A`
    - **Salida**: `"% "` (justificado a la izquierda).

---

### **Tabla compacta de combinaciones de casos a evaluar**

| **Conversión** | **Flags/Combinación** | **Entrada** | **Salida esperada** |
| --- | --- | --- | --- |
| `%d` | `-` | `"%-10d"`, `42` | `"42        "` |
| `%d` | `0` | `"%010d"`, `42` | `"0000000042"` |
| `%d` | `.` | `"%10.5d"`, `42` | `"     00042"` |
| `%s` | `-` | `"%-10s"`, `"abc"` | `"abc       "` |
| `%s` | `.` | `"%10.2s"`, `"abc"` | `"        ab"` |
| `%p` | `-` | `"%-15p"`, `(void *)0x1234` | `"0x1234         "` |
| `%p` | `NULL` | `"%p"`, `(void *)0` | `"(nil)"` |
| `%u` | `0` | `"%010u"`, `123` | `"0000000123"` |
| `%x` | `#` | `"%#x"`, `123` | `"0x7b"` |
| `%X` | `#` | `"%#10X"`, `123` | `"      0X7B"` |
| `%d` | `+` | `"%+d"`, `42` | `"+42"` |
| `%d` | `' '` | `"% d"`, `42` | `" 42"` |
| `%d` | `+` | `"%+d"`, `-42` | `"-42"` |
| `%o` | `#` | `"%#o"`, `123` | `"0173"` |
| `%d` | Contradicción `-0` | `"%-010d"`, `42` | `"42        "` |
| `%d` | Contradicción `0.` | `"%0.5d"`, `42` | `"00042"` |
| `%x` | `#`, precisión y ancho | `"%#10.5x"`, `123` | `"   0x0007b"` |
| `%d` | `+`, precisión y ancho | `"%+10.5d"`, `-42` | `"   -00042"` |
| `%c` | Ancho mínimo `-` | `"%-5c"`, `'A'` | `"A    "` |
| `%s` | Precisión y nulo | `"%.5s"`, `NULL` | `"(null)"` |
| `%u` | Precisión con cero | `"%.0u"`, `0` | `""` |
| `%x` | `#` con cero | `"%#x"`, `0` | `"0"` |
| `%` | Ancho mínimo | `"%5%"`, `N/A` | `"    %"` |
| `%` | Ancho mínimo `-` | `"%-5%"`, `N/A` | `"%    "` |

---

### **Casos adicionales de validación**

### **1. Casos contradictorios**

- **Entrada**: `"%-010d"`, `42`
    - **Explicación**: El flag `` (justificar a la izquierda) anula `0` (relleno con ceros).
    - **Salida esperada**: `"42 "`.
- **Entrada**: `"%0.5d"`, `42`
    - **Explicación**: La precisión anula el flag `0`.
    - **Salida esperada**: `"00042"`.

### **2. Flags no aplicables**

- **Entrada**: `"%#d"`, `42`
    - **Explicación**: El flag `#` no tiene efecto con enteros decimales.
    - **Salida esperada**: `"42"`.
- **Entrada**: `"%#s"`, `"hello"`
    - **Explicación**: El flag `#` no aplica para strings.
    - **Salida esperada**: `"hello"`.

### **3. Precisión y valores cero**

- **Entrada**: `"%.0d"`, `0`
    - **Explicación**: La precisión `0` elimina el número si es cero.
    - **Salida esperada**: `""`.
- **Entrada**: `"%.0s"`, `"abc"`
    - **Explicación**: Para strings, precisión `0` da una salida vacía.
    - **Salida esperada**: `""`.

### **4. Combinaciones extremas**

- **Entrada**: `"%#10.5x"`, `123`
    - **Explicación**: Prefijo `0x`, ancho mínimo de 10 y precisión de 5.
    - **Salida esperada**: `" 0x0007b"`.
- **Entrada**: `"%+10.5d"`, `42`
    - **Explicación**: Signo `+`, precisión 5, ancho mínimo 10.
    - **Salida esperada**: `" -00042"`.

---

```c
typedef struct s_print                       
{                        
      va_list  args;    # arg to print out                    
      int   wdt;        # width                
      int   prc;        # precision              
      int   zero;       # zero padding               
      int   pnt;        # .     
      int   dash;       # -               
      int   tl;         # total_length (return value)              
      int   sign;       # pos or neg number               
      int   is_zero;    # is number zero                 
      int   perc;       # %               
      int   sp;         # space flag ' '            
}    t_print;
```

```c
t_print *ft_initialise_tab(t_print *tab)                       
{                       
      tab->wdt = 0;        # we set everything to 0, false        
      tab->prc = 0;                        
      tab->zero = 0;                        
      tab->pnt = 0;                        
      tab->sign = 0;                        
      tab->tl = 0;                        
      tab->is_zero = 0;                        
      tab->dash = 0;                        
      tab->perc = 0;                        
      tab->sp = 0;                        
      return (tab);                       
}
int ft_printf(const char *format, ...)
{
   t_print *tab;
                       
   tab = (t_print *)malloc(sizeof(t_print));                        
   if (!tab)                         
       return (-1);
   ft_initialise_tab(tab)
}
```

```c
int ft_printf(const char *format, ...)
{
   int i;
   int ret;
   t_print *tab;
                       
   tab = (t_print *)malloc(sizeof(t_print));                        
   if (!tab)                         
       return (-1);
   ft_initialise_tab(tab)
   va_start(tab->args, format);
   i = -1;
   ret = 0;
   while (format[++i]) // while the string exists
   { 
      if (format[i] == '%') //if the current char is %
         i = ft_eval_format(tab, format, i + 1); // evaluate format**
      else
         ret += write(1, &format[i], 1); // print what you read
    }
    va_end(tab->args);
    ret += tab->tl;
    free (tab);
    return (ret);
}
```
