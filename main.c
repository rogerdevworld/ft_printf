#include "./include/ft_printf_bonus.h"

void test_minus_sign(void)
{
    void *ptr = (void *)0x1234;
    int num = 42;
    unsigned int unum = 42;

    int len1, len2;

    ft_printf("\n===== Test del signo '-' =====\n");

    // Prueba con punteros
    ft_printf("\nTest del signo '-' en punteros %%-20p\n");
    len1 = printf("1. [%-20p]\n", ptr) - 6;
    len2 = ft_printf("1. [%-20p]\n", ptr) - 6;
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros con signo (i)
    ft_printf("\nTest del signo '-' en enteros con signo %%-10i\n");
    len1 = printf("2. [%-10i]\n", num) - 6;
    len2 = ft_printf("2. [%-10i]\n", num) - 6;
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros con signo (d)
    ft_printf("\nTest del signo '-' en digit %%-10i\n");
    len1 = printf("3. [%-10d]\n", num) - 6;
    len2 = ft_printf("3. [%-10d]\n", num) - 6;
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros sin signo
    ft_printf("\nTest del signo '-' en enteros sin signo %%-10u\n");
    len1 = printf("4. [%-10u]\n", unum) - 6;
    len2 = ft_printf("4. [%-10u]\n", unum) - 6;
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con hexadecimal minúscula
    ft_printf("\nTest del signo '-' en hexadecimal minúscula %%-10x\n");
    len1 = printf("5. [%-10x]\n", num) - 6;
    len2 = ft_printf("5. [%-10x]\n", num) - 6;
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con hexadecimal mayúscula
    ft_printf("\nTest del signo '-' en hexadecimal mayúscula %%-10X\n");
    len1 = printf("6. [%-10X]\n", num) - 6;
    len2 = ft_printf("6. [%-10X]\n", num) - 6;
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);
}


void test_plus_sign(void)
{
    int num_pos = 42;
    int num_neg = -42;
    unsigned int unum = 42;

    int len1, len2;

    ft_printf("\n===== Test del signo '+' =====\n");

    // Prueba con enteros con signo positivos
    ft_printf("\nTest del signo '+' en enteros positivos\n");
    len1 = printf("1. [%+10i]\n", num_pos);
    len2 = ft_printf("1. [%+10i]\n", num_pos);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    len1 = printf("2. [%+10d]\n", num_pos);
    len2 = ft_printf("2. [%+10d]\n", num_pos);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros negativos (el '+' no afecta, pero lo probamos)
    ft_printf("\nTest del signo '+' en enteros negativos\n");
    len1 = printf("3. [%+10i]\n", num_neg);
    len2 = ft_printf("3. [%+10i]\n", num_neg);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    len1 = printf("4. [%+10d]\n", num_neg);
    len2 = ft_printf("4. [%+10d]\n", num_neg);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros sin signo (el '+' no tiene efecto aquí)
    ft_printf("\nTest del signo '+' en enteros sin signo (no debería afectar)\n");
    len1 = printf("5. [%10u]\n", unum);
    len2 = ft_printf("5. [%10u]\n", unum);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);
}

void test_zero_sign(void)
{
    void *ptr = (void *)0x1234;
    int num = 42;
    unsigned int unum = 42;

    int len1, len2;

    ft_printf("\n===== Test del signo '0' =====\n");

    // Prueba con punteros
    ft_printf("\nTest del signo '0' en punteros\n");
    len1 = printf("1. [%20p]\n", ptr);
    len2 = ft_printf("1. [%020p]\n", ptr);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros con signo
    ft_printf("\nTest del signo '0' en enteros con signo\n");
    len1 = printf("2. [%010i]\n", num);
    len2 = ft_printf("2. [%010i]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    len1 = printf("3. [%010d]\n", num);
    len2 = ft_printf("3. [%010d]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros sin signo
    ft_printf("\nTest del signo '0' en enteros sin signo\n");
    len1 = printf("4. [%010u]\n", unum);
    len2 = ft_printf("4. [%010u]\n", unum);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con hexadecimal minúscula
    ft_printf("\nTest del signo '0' en hexadecimal minúscula\n");
    len1 = printf("5. [%010x]\n", num);
    len2 = ft_printf("5. [%010x]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con hexadecimal mayúscula
    ft_printf("\nTest del signo '0' en hexadecimal mayúscula\n");
    len1 = printf("6. [%010X]\n", num);
    len2 = ft_printf("6. [%010X]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);
}

void test_hash_sign(void)
{
    int num = 42;
    unsigned int unum = 42;

    int len1, len2;

    ft_printf("\n===== Test del signo '#' =====\n");

    // Prueba con enteros con signo
    ft_printf("\nTest del signo '#' en enteros con signo\n");
    len1 = printf("1. [%#10i]\n", num);
    len2 = ft_printf("1. [%#10i]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    len1 = printf("2. [%#10d]\n", num);
    len2 = ft_printf("2. [%#10d]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros sin signo
    ft_printf("\nTest del signo '#' en enteros sin signo\n");
    len1 = printf("3. [%#10u]\n", unum);
    len2 = ft_printf("3. [%#10u]\n", unum);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con hexadecimal minúscula
    ft_printf("\nTest del signo '#' en hexadecimal minúscula\n");
    len1 = printf("4. [%#10x]\n", num);
    len2 = ft_printf("4. [%#10x]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con hexadecimal mayúscula
    ft_printf("\nTest del signo '#' en hexadecimal mayúscula\n");
    len1 = printf("5. [%#10X]\n", num);
    len2 = ft_printf("5. [%#10X]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);
}

void test_space_sign(void)
{
    int num_pos = 42;
    int num_neg = -42;
    unsigned int unum = 42;

    int len1, len2;

    ft_printf("\n===== Test del signo ' ' (espacio) =====\n");

    // Prueba con enteros con signo positivos
    ft_printf("\nTest del signo ' ' en enteros positivos\n");
    len1 = printf("1. [% 10i]\n", num_pos);
    len2 = ft_printf("1. [% 10i]\n", num_pos);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    len1 = printf("2. [% 10d]\n", num_pos);
    len2 = ft_printf("2. [% 10d]\n", num_pos);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros negativos
    ft_printf("\nTest del signo ' ' en enteros negativos\n");
    len1 = printf("3. [% 10i]\n", num_neg);
    len2 = ft_printf("3. [% 10i]\n", num_neg);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    len1 = printf("4. [% 10d]\n", num_neg);
    len2 = ft_printf("4. [% 10d]\n", num_neg);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros sin signo (espacio no se aplica)
    ft_printf("\nTest del signo ' ' en enteros sin signo (no debería afectar)\n");
    len1 = printf("5. [% 10u]\n", unum);
    len2 = ft_printf("5. [% 10u]\n", unum);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);
}

void test_precision_dot(void)
{
    int num = 42;
    unsigned int unum = 42;

    int len1, len2;

    ft_printf("\n===== Test del signo '.' (precisión) =====\n");

    // Prueba con enteros con precisión
    ft_printf("\nTest del signo '.' en enteros con precisión\n");
    len1 = printf("1. [%.5i]\n", num);
    len2 = ft_printf("1. [%.5i]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    len1 = printf("2. [%.5d]\n", num);
    len2 = ft_printf("2. [%.5d]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con enteros sin signo
    ft_printf("\nTest del signo '.' en enteros sin signo\n");
    len1 = printf("3. [%.5u]\n", unum);
    len2 = ft_printf("3. [%.5u]\n", unum);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con hexadecimal minúscula
    ft_printf("\nTest del signo '.' en hexadecimal minúscula\n");
    len1 = printf("4. [%.5x]\n", num);
    len2 = ft_printf("4. [%.5x]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);

    // Prueba con hexadecimal mayúscula
    ft_printf("\nTest del signo '.' en hexadecimal mayúscula\n");
    len1 = printf("5. [%.5X]\n", num);
    len2 = ft_printf("5. [%.5X]\n", num);
    printf("Len printf: %d, Len ft_printf: %d\n\n", len1, len2);
}

int main(void)
{
    test_minus_sign();
    test_plus_sign();
    test_zero_sign();
    test_hash_sign();
    test_space_sign();
    test_precision_dot();
    return 0;
}