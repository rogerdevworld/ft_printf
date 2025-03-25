# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -g
LDFLAGS = -L. -lftprintf
INCLUDES = -I.

# Files
SRC = ft_printf_tester.cpp
OBJ = $(SRC:.cpp=.o)
NAME = ft_printf_tester

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test: all
	@./$(NAME)

test_bonus: all
	@./$(NAME) bonus

leaks: all
	@./$(NAME) leaks

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test test_bonus leaks