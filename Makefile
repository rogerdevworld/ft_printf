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

# ---------------------------- CONFIGURACIÓN -------------------------------- #

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

# --- Compartido --- #
SHARED_DIR  = ./src/shared
SHARED_SRCS = ft_validation.c
SHARED_OBJS = $(addprefix $(OBJ_DIR)/, $(SHARED_SRCS:.c=.o))

# --- Mandatory --- #
SRC_DIR     = ./src/mandatory
SRCS        = ft_printf.c ft_printf_utils.c ft_flags.c
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# --- Bonus --- #
BSRC_DIR    = ./src/bonus
BSRCS       = ft_printf_bonus.c ft_init.c ft_apply.c ft_utils.c ft_hex.c \
              ft_integer.c ft_pointer.c ft_string.c utils.c ft_char.c \
              ft_percent.c ft_unsigned.c
BOBJS       = $(addprefix $(OBJ_DIR)/, $(BSRCS:.c=.o))

# --- Tester --- #
PRINTFTESTER = ./printfTester

# -------------------------- LÓGICA DE COMPILACIÓN -------------------------- #

ifdef BONUS
	SOURCES := $(BSRCS)
	OBJECTS := $(BOBJS) $(SHARED_OBJS)
	HEADER  := $(HEADER_BONUS)
	SRC_DIR := $(BSRC_DIR)
else
	SOURCES := $(SRCS)
	OBJECTS := $(OBJS) $(SHARED_OBJS)
	SRC_DIR := ./src/mandatory
endif

# ---------------------------- REGLAS -------------------------------------- #

all: libft $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SHARED_DIR)/%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Compilando $(NAME)...$(RESET)"
	@ar rcs $(NAME) $(OBJECTS) $(LIBFT)
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
		git clone https://github.com/rogerdevworld/libftall.git $(LIBFT_DIR); \
	fi
	@$(MAKE) -C $(LIBFT_DIR)

test:
	@if [ ! -d "$(PRINTFTESTER)" ]; then \
		echo "$(RED)Descargando tester...$(RESET)"; \
		git clone https://github.com/Tripouille/printfTester.git $(PRINTFTESTER); \
	fi
	@$(MAKE)
	@$(MAKE) bonus
	@echo "$(GREEN)Test Mandatory...$(RESET)"
	@make -C $(PRINTFTESTER) m
	@$(MAKE) clean
	@echo "$(GREEN)Test Bonus...$(RESET)"
	@make -C $(PRINTFTESTER) b
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
	@$(RM) $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus libft test
