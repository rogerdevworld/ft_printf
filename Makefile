NAME = libftprintf.a
SRC = ft_printf.c ft_flags.c ft_printf_utils.c
OBJS = $(SRC:.c = .o)
HEADER = libftprintf.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rsc $(NAME) $(OBJS)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY : all clean fclean re