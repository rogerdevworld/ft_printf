#include "include/ft_printf.h"
#include <stdio.h>

int main(void)
{
    int len;

    // Test 00: Poteccion de write(); todo debe imprimir -1

    // Test 1: Imprimir una cadena simple
    len = ft_printf("Hola, mundo!\n");
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 2: Imprimir un solo carácter
    len = ft_printf("Un carácter: %c\n", 'A');
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 3: Imprimir una cadena con un valor NULL
    len = ft_printf("Cadena nula: %s\n", NULL);
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 4: Imprimir un número entero
    len = ft_printf("Número entero: %d\n", 12345);
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 5: Imprimir un número unsigned
    len = ft_printf("Número unsigned: %u\n", 12345);
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 6: Imprimir un número hexadecimal en minúsculas
    len = ft_printf("Número hexadecimal (minúsculas): %x\n", 123456);
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 7: Imprimir un número hexadecimal en mayúsculas
    len = ft_printf("Número hexadecimal (mayúsculas): %X\n", 123456);
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 8: Imprimir un puntero
    int *ptr = &len;
    len = ft_printf("Puntero: %p\n", ptr);
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 9: Imprimir un porcentaje
    len = ft_printf("Imprimir porcentaje: %%\n");
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 10: Imprimir un porcentaje al final de la cadena
    len = ft_printf("Fin con porcentaje: %%\n");
    printf("Longitud de la cadena impresa: %d\n", len);

    // Test 11: Imprimir un '%' solo fortmat
    len = ft_printf("Texto con porcentaje %% solo: \n% en medio\n");
    printf("Longitud de la cadena impresa: %d\n", len);
   
    //Test 12: Retornar -1 print hasta %
    printf("\nCaso de error origninal -1: %i", printf("antes \n% despues\n"));
    ft_printf("\nCaso de error copia -1: %i", ft_printf("antes \n% despues\n"));
    return 0;
}

