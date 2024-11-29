NAME = libftprintf.a
SRC = ./src/mandaroty/ft_printf.c ./src/mandaroty/ft_flags.c ./src/mandatory/ft_printf_utils.c
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
