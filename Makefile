NAME = libftprintf.a

#Mandatory
SRC = src/mandatory/ft_printf.c src/mandatory/ft_flags.c src/mandatory/ft_printf_utils.c
OBJS = $(SRC:.c=.o)

#Bonus
BSRC = src/bonus/ft_printf_bonus.c
BOBJS = $(BSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rsc

#color
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

ifdef BONUS
	HEADER = ft_printf_bonus.h
	OBJECTS = $(BOBJS)
else
	HEADER = ft_printf.h
	OBJECTS = $(OBJS)
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Compilando...$(RESET)"
	ar rsc $(NAME) $?
	ranlib $(NAME)
	@echo "$(BLUE)"
	@echo "$(YELLOW)           (__)\           $(RESET)"
	@echo "$(YELLOW)           (oo)\\________  $(RESET)"
	@echo "$(RESET)           /|| \\        \\ $(RESET)"
	@echo "$(RESET)              ||------w | $(RESET)"
	@echo "$(RESET)              ||       || $(RESET)"
	@echo "$(YELLOW)THE COW MAKES MUUUUUUUUUU!$(RESET)"
	@echo "$(RESET)"

bonus: $(OBJS) $(BOBJS)
#@$(MAKE) BONUS=42 --no-print-directory
	@echo "$(GREEN)Compilando...$(RESET)"
	ar rsc $(NAME) $?
	ranlib $(NAME)
	@echo "$(BLUE)"
	@echo "$(YELLOW)           (__)\           $(RESET)"
	@echo "$(YELLOW)           (oo)\\________  $(RESET)"
	@echo "$(RESET)           /|| \\        \\ $(RESET)"
	@echo "$(RESET)              ||------w | $(RESET)"
	@echo "$(RESET)              ||       || $(RESET)"
	@echo "$(YELLOW)THE COW MAKES MUUUUUUUUUU!$(RESET)"
	@echo "$(RESET)"

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(GREEN)Delete .o, wait..$(RESET)"
	$(RM) $(OBJS)

fclean: clean
	@echo "$(GREEN)Delete... all$(RESET)"
	$(RM) $(NAME)
	
re: fclean all

.PHONY : all clean fclean re
