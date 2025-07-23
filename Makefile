# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:58:52 by rmarrero          #+#    #+#              #
#    Updated: 2025/02/17 11:55:01 by rmarrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Shared --- #
OBJ_DIR = ./obj

# --- Mandatory --- #
NAME = libftprintf.a
SRC_DIR = ./src/mandatory/


SRCS =	$(SRC_DIR)ft_printf.c $(SRC_DIR)ft_printf_utils.c $(SRC_DIR)ft_flags.c $(SRC_DIR)ft_validation.c
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

# --- Bonus --- #
BSRC_DIR = ./src/bonus/
BSRCS =	$(BSRC_DIR)ft_printf_bonus.c \
		$(BSRC_DIR)ft_init.c $(BSRC_DIR)ft_apply.c \
		$(BSRC_DIR)ft_utils.c $(BSRC_DIR)ft_hex.c $(BSRC_DIR)ft_integer.c \
		$(BSRC_DIR)ft_pointer.c $(BSRC_DIR)ft_string.c $ $(BSRC_DIR)ft_char.c $(BSRC_DIR)ft_validation.c \
		$(BSRC_DIR)ft_percent.c $(BSRC_DIR)ft_unsigned.c $(BSRC_DIR)ft_isdigit.c $(BSRC_DIR)ft_strlen.c

BOBJS = $(BSRCS:$(BSRC_DIR)%.c=$(OBJ_DIR)/%.o)

# --- Tester --- #
PRINTFTESTER = ./printfTester

CC = cc
CFLAGS = -Wall -Werror -Wextra -I./include 
#-fsanitize=address
RM = rm -rf

OBJECTS = $(OBJS) $(SHARED_OBJS)
HEADER = ./include/ft_printf.h

# Condicional para determinar si se compilan los bonus
ifdef BONUS
	OBJECTS = $(BOBJS) $(SHARED_OBJS)
	HEADER = ./include/ft_printf_bonus.h
	SRC_DIR = ./src/bonus/
endif

# Colores para la terminal
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

# Regla principal
all: $(NAME)

# Asegurar que el directorio obj existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilación de archivos fuente a objetos (para cualquier fuente)
$(OBJ_DIR)/%.o: $(SRC_DIR)%.c $(HEADER) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SHARED_DIR)%.c $(HEADER) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Creación de la librería estática
$(NAME): $(OBJECTS) $(HEADER) Makefile
	@echo "$(GREEN)Compilando $(NAME)...$(RESET)"
	ar rsc $(NAME) $(OBJECTS) $(LIBFT)
	@echo "$(BLUE)"
	@echo "$(YELLOW)           ($(RESET)__$(YELLOW))\           $(RESET)"
	@echo "$(YELLOW)           ($(RESET)oo$(YELLOW))\\________  $(RESET)"
	@echo "$(RESET)           /|| \\        \\ $(NAME) ready$(RESET)"
	@echo "$(RESET)              ||------w | $(RESET)"
	@echo "$(RESET)              ||       || $(RESET)"
	@echo "$(YELLOW)THE COW MAKES MUUUUUUUUUU!$(RESET)"
	@echo "$(RESET)"

# Regla para compilar el bonus
bonus:
	rm -rf libftprintf.a
	@$(MAKE) BONUS=42 all --no-print-directory
	@echo "$(GREEN)Compilando bonus...$(RESET)"

test:
	@if [ ! -d "$(PRINTFTESTER)" ]; then \
		echo "$(RED)La carpeta $(PRINTFTESTER) no existe. Descargando tester...$(RESET)"; \
		git clone https://github.com/Tripouille/printfTester.git $(PRINTFTESTER); \
	fi

	make 
	make bonus
	@echo "$(GREEN)Test Mandatory...$(RESET)"
	@make -C $(PRINTFTESTER) m

	make clean

	@echo "$(GREEN)Test Bonus...$(RESET)"
	@make -C $(PRINTFTESTER) b

	@echo "$(GREEN)Test Mandatory (+Bonus)...$(RESET)"
	@make -C $(PRINTFTESTER) a

# Limpieza de archivos objeto
clean:
	@echo "$(GREEN)Eliminando archivos objeto...$(RESET)"
	$(RM) $(OBJ_DIR)

# Limpieza total
fclean: clean
	@echo "$(GREEN)Eliminando ejecutable y librerías...$(RESET)"
	$(RM) -f $(NAME)

	@echo "$(GREEN)clean bonus$(RESET)"
	$(RM) $(OBJ_DIR)

# Regeneración completa
re: fclean all

.PHONY: all clean fclean bonus
