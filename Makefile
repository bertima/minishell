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
	   \
	   src/error_free/error.c \
	   src/error_free/free.c \
	   \
	   \
	   src/init_data/prompt.c \
	   src/init_data/creat_env.c \
	   src/init_data/init_struct.c \
	   \
	   \
	   src/parsing/parser/parsing.c \
	   src/parsing/parser/creat_command.c \
	   src/parsing/parser/add_command_argument.c \
	   src/parsing/parser/manage_redirect_token.c \
	   \
	   src/parsing/token/creat_token.c \
	   src/parsing/token/metacharactere.c \
	   \
	   src/parsing/lexeur/lexeur.c \
	   \
	   \
	   src/signal/signal.c\
	   \
	   \
	   src/expand/expand.c \
	   src/expand/expand_utils/ft_valid_expand.c \
	   src/expand/expand_utils/search_exp_exit_code.c \
	   src/expand/expand_utils/expand_manage.c \
	   src/expand/expand_utils/remove_quote_search_name.c \
	   src/expand/expand_utils/insert_arg_expand.c \
	   src/expand/expand_utils/suppress_arg.c \
	   \
	   \
	   src/here_doc/creat_file_generator.c \
	   src/here_doc/here_doc.c \
	   \
	   \
	   src/exec/exec.c \
	   \
	   src/exec/exec_utils/redirection/redirect_std_close.c \
	   src/exec/exec_utils/redirection/redirection.c \
	   \
	   src/exec/exec_utils/execut_builtin_command.c \
	   src/exec/exec_utils/execve.c \
	   src/exec/exec_utils/children.c \
	   \
	   src/exec/builtin/echo.c \
	   src/exec/builtin/env.c \
	   src/exec/builtin/exit.c\
	   src/exec/builtin/pwd.c\
	   src/exec/builtin/cd.c\
	   src/exec/builtin/cd_utils.c\
	   src/exec/builtin/export/export.c\
	   src/exec/builtin/export/export_utils.c\
	   src/exec/builtin/export/export_utils2.c\
	   src/exec/builtin/unset.c\
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
