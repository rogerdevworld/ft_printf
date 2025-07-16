# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:58:52 by rmarrero          #+#    #+#              #
#    Updated: 2025/07/16 12:00:00 by rmarrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------- CONFIGURACIÓN -------------------------------- #

NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I./include
RM          = rm -rf

OBJ_DIR     = obj
HEADER      = ./include/ft_printf.h
HEADER_BONUS= ./include/ft_printf_bonus.h

# --- Colores --- #
GREEN   = \033[32m
YELLOW  = \033[33m
RED     = \033[31m
BLUE    = \033[34m
RESET   = \033[0m

# --- Librería libft --- #
LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

# ----------------------------- FUENTES ------------------------------------- #

# --- Mandatory --- #
MANDATORY_DIR = ./src/mandatory
MANDATORY_SRCS = ft_printf.c ft_printf_utils.c ft_flags.c ft_validation.c
MANDATORY_OBJS = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRCS:.c=.o))

# --- Bonus --- #
BONUS_DIR = ./src/bonus
BONUS_SRCS = ft_printf_bonus.c ft_init.c ft_apply.c ft_hex.c \
             ft_integer.c ft_pointer.c ft_string.c utils.c ft_char.c \
             ft_percent.c ft_unsigned.c ft_validation.c
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

# --- Tester --- #
PRINTFTESTER = ./printfTester

# -------------------------- LÓGICA DE COMPILACIÓN -------------------------- #

ifdef BONUS
	SRC_DIR  := $(BONUS_DIR)
	SRCS     := $(BONUS_SRCS)
	OBJECTS  := $(BONUS_OBJS) $(LIBFT)
	HEADER   := $(HEADER_BONUS)
else
	SRC_DIR  := $(MANDATORY_DIR)
	SRCS     := $(MANDATORY_SRCS)
	OBJECTS  := $(MANDATORY_OBJS)
endif

# ---------------------------- REGLAS -------------------------------------- #

all: libft $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Compilando $(NAME)...$(RESET)"
	@ar rcs $(NAME) $(OBJECTS)
	@echo "$(BLUE)"
	@echo "$(YELLOW)           ($(RESET)__$(YELLOW))\           $(RESET)"
	@echo "$(YELLOW)           ($(RESET)oo$(YELLOW))\\________  $(RESET)"
	@echo "$(RESET)           /|| \\        \\ $(NAME) ready$(RESET)"
	@echo "$(RESET)              ||------w | $(RESET)"
	@echo "$(RESET)              ||       || $(RESET)"
	@echo "$(YELLOW)THE COW MAKES MUUUUUUUUUU!$(RESET)"

bonus:
	@$(MAKE) BONUS=1 all --no-print-directory
	@echo "$(GREEN)Compilando bonus...$(RESET)"

libft:
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(GREEN)Clonando libft...$(RESET)"; \
		git clone https://github.com/rogerdevworld/libft.git $(LIBFT_DIR); \
	fi
	@$(MAKE) -C $(LIBFT_DIR)

test:
	@if [ ! -d "$(PRINTFTESTER)" ]; then \
		echo "$(RED)Descargando tester...$(RESET)"; \
		git clone https://github.com/Tripouille/printfTester.git $(PRINTFTESTER); \
	fi
	@$(MAKE) bonus
	@echo "$(GREEN)Test Mandatory + Bonus...$(RESET)"
	@make -C $(PRINTFTESTER) a

clean:
	@echo "$(GREEN)Limpiando objetos...$(RESET)"
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(GREEN)Limpiando ejecutable y tester...$(RESET)"
	@$(RM) $(NAME) $(PRINTFTESTER)
	@make -C $(LIBFT_DIR) fclean
	@$(RM) -rf $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus libft test
