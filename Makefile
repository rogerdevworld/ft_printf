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

NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I./include
RM          = rm -rf

OBJ_DIR     = obj
HEADER      = ./include/ft_printf.h
HEADER_BONUS= ./include/ft_printf_bonus.h

# ------------------------ FUENTES ------------------------------------------ #

# Mandatory
MANDATORY_DIR  = ./src/mandatory
MANDATORY_SRCS = ft_printf.c ft_printf_utils.c ft_flags.c ft_validation.c
MANDATORY_OBJS = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRCS:.c=.o))

# Bonus
BONUS_DIR   = ./src/bonus
BONUS_SRCS  = ft_printf_bonus.c ft_init.c ft_apply.c ft_hex.c \
              ft_integer.c ft_pointer.c ft_string.c utils.c ft_char.c \
              ft_percent.c ft_unsigned.c ft_validation.c ft_isdigit.c ft_strlen.c
BONUS_OBJS  = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

# ------------------------ LÓGICA ------------------------------------------- #

ifdef BONUS
	SRC_DIR := $(BONUS_DIR)
	SRCS    := $(BONUS_SRCS)
	OBJS    := $(BONUS_OBJS)
	HEADERS := $(HEADER_BONUS)
else
	SRC_DIR := $(MANDATORY_DIR)
	SRCS    := $(MANDATORY_SRCS)
	OBJS    := $(MANDATORY_OBJS)
	HEADERS := $(HEADER)
endif

# ------------------------ REGLAS ------------------------------------------- #

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Compilando $(NAME)..."
	@ar rcs $(NAME) $(OBJS)

bonus:
	@$(MAKE) BONUS=1 all --no-print-directory
	@echo "Compilado con soporte bonus."

clean:
	@echo "Limpiando objetos..."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Limpiando archivo $(NAME)..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
