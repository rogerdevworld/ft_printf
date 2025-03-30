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

# --- Mandatory --- #
NAME = libftprintf.a
SRC_DIR = ./src/mandatory/
OBJ_DIR = ./obj

SRCS =	$(SRC_DIR)ft_printf.c $(SRC_DIR)ft_printf_utils.c $(SRC_DIR)ft_flags.c
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

# --- Bonus --- #
BSRC_DIR = ./src/bonus/
BSRCS =	$(BSRC_DIR)ft_printf_bonus.c
BOBJS = $(BSRCS:$(BSRC_DIR)%.c=$(OBJ_DIR)/%.o)

# --- Tester --- #
PRINTFTESTER = ./printfTester

CC = cc
CFLAGS = -Wall -Werror -Wextra -I./include
RM = rm -rf

OBJECTS = $(OBJS)
HEADER = ./include/ft_printf.h

# Condicional para determinar si se compilan los bonus
ifdef BONUS
	OBJECTS = $(BOBJS)
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

# Creación de la librería estática
$(NAME): $(OBJECTS) $(HEADER)
	@echo "$(GREEN)Compilando $(NAME)...$(RESET)"
	ar rsc $(NAME) $(OBJECTS)
	@echo "$(BLUE)"
	@echo "$(YELLOW)           ($(RESET)__$(YELLOW))\           $(RESET)"
	@echo "$(YELLOW)           ($(RESET)oo$(YELLOW))\\________  $(RESET)"
	@echo "$(RESET)           /|| \\        \\ $(NAME) ready$(RESET)"
	@echo "$(RESET)              ||------w | $(RESET)"
	@echo "$(RESET)              ||       || $(RESET)"
	@echo "$(YELLOW)THE COW MAKES MUUUUUUUUUU!$(RESET)"
	@echo "$(RESET)"

# Regla para compilar el bonus
#bonus: 
bonus:
	@$(MAKE) BONUS=42 --no-print-directory
	@echo "$(GREEN)Compilando bonus...$(RESET)"

test:
	@if [ ! -d "$(PRINTFTESTER)" ]; then \
		echo "$(RED)La carpeta $(PRINTFTESTER) no existe. Descargando tester...$(RESET)"; \
		git clone https://github.com/Tripouille/printfTester.git $(PRINTFTESTER); \
	fi
	@echo "$(GREEN)Test Mandatory...$(RESET)"
	@make -C $(PRINTFTESTER) m

	make fclean

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

	# Eliminar los objetos generados para bonus si están presentes
	$(RM) $(OBJ_DIR)/ft_printf_bonus.o

	# Eliminar tester
#$(RM) $(PRINTFTESTER)

# Regeneración completa
re: fclean all

.PHONY: all clean fclean re bonus
