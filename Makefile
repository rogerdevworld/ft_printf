NAME = libftprintf.a
SRC = ./src/ft_printf.c ./src/ft_flags.c ./src/ft_printf_utils.c
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
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY : all clean fclean re
