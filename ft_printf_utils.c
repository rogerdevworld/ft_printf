
int is_flag(char c)
{
    return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X');
}

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
