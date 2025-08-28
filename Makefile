# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 15:06:45 by bertrmar          #+#    #+#              #
#    Updated: 2025/08/11 15:06:47 by bertrmar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------EXEC/FLAGS--------------------#

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

#----------------------HEADER----------------------#

INCLUDE = ./include
LIBFT_DIR = ./src/libft

#---------------------LIBRARIE---------------------#

LIBFT = $(LIBFT_DIR)/libft.a
LIB_READ = -lreadline -lncurses

#----------------------DIRECT----------------------#

OBJDIR = object

#--------------------SRC/OBJECT--------------------#

FSRC = src/main.c \
	   src/error_free/error.c \
	   src/error_free/free.c \
	   \
	   src/init_data/prompt.c \
	   src/init_data/init_struct.c \
	   \
	   src/parsing/parsing.c \
	   src/parsing/quote.c \
	   src/parsing/tokening.c \
	   \
	   src/exec/exec.c \
	   \
	   src/builtin/echo.c

OBJ_FILES = $(patsubst src/%.c,$(OBJDIR)/%.o,$(FSRC))

#-----------------------RULE-----------------------#

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(LIB_READ) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "$(NAME) ok"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@rm -rf object
	@make clean -s -C $(LIBFT_DIR)
	@echo "obj clean"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@echo "name exec clean"

re: fclean all

.PHONY: clean fclean all re