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
LIBFT_DIR = ./libft

#---------------------LIBRARIE---------------------#

LIBFT = $(LIBFT_DIR)/libft.a
LIB_READ = -lreadline -lncurses

#----------------------DIRECT----------------------#

OBJDIR = object

#--------------------SRC/OBJECT--------------------#

FSRC = src/main.c \
	   \
	   src/error_free/error.c \
	   src/error_free/free.c \
	   \
	   src/init_data/prompt.c \
	   src/init_data/init_struct.c \
	   \
	   \
	   src/parsing/parser/parsing.c \
	   src/parsing/parser/creat_command.c \
	   src/parsing/parser/add_command_argument.c \
	   src/parsing/parser/redirect.c \
	   \
	   src/parsing/token/creat_token.c \
	   src/parsing/token/metacharactere.c \
	   \
	   src/parsing/lexeur/lexeur.c \
	   \
	   \
	   src/exec/exec.c \
	   \
	   src/expand/expand.c \
	   src/expand/expand_here_doc.c \
	   src/expand/var_exist.c \
	   src/expand/remove_quote.c \
	   \
	   src/exec/builtin/echo.c \
	   src/exec/builtin/env.c \
	   \
	   \
	   \
	   \
	   \
	   src/testeur/test.c

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