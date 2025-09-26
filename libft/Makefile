# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 10:53:44 by bertrmar          #+#    #+#              #
#    Updated: 2025/08/12 08:40:41 by bertrmar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------EXEC/FLAGS--------------------#

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra 

#----------------------HEADER----------------------#

INCLUDE = include

#----------------------DIRECT----------------------#

OBJDIR = object
GNL_DIR = get_next_line
PRINTF_DIR = printf

#---------------------LIBRARIE---------------------#

LIBFT = $(LIBFT_DIR)/libft.a

#--------------------SRC/OBJECT--------------------#

FSRC = ft_abs.c \
       ft_atoi.c \
       ft_atol.c \
       ft_atoll.c \
       ft_bzero.c \
       ft_calloc.c \
       ft_strcat.c \
       ft_check_base.c \
       ft_free_split.c \
       ft_isalnum.c \
       ft_isalpha.c \
       ft_isascii.c \
       ft_isdigit.c \
       ft_isprint.c \
       ft_isspace.c \
       ft_itoa.c \
       ft_len_double_char.c \
       ft_ltoa.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_memset.c \
       ft_putnbr_base.c \
       ft_putchar_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_putnbr_unsigned.c \
       ft_putstr_fd.c \
       ft_split_chr.c \
       ft_split.c \
       ft_strchr.c \
       ft_strcmp.c \
       ft_strcpy.c \
       ft_striteri.c \
       ft_strdup.c \
       ft_strjoin.c \
       ft_strjoin_var.c \
       ft_strlcat.c \
       ft_strlcpy.c \
       ft_strlen.c \
       ft_strmapi.c \
       ft_strncmp.c \
       ft_strnstr.c \
       ft_strrchr.c \
       ft_strstr.c \
       ft_strtrim.c \
       ft_substr.c \
       ft_tolower.c \
       ft_toupper.c \
       ft_lstadd_back.c \
       ft_lstadd_front.c \
       ft_lstclear.c \
       ft_lstdelone.c \
       ft_lstiter.c \
       ft_lstlast.c \
       ft_lstnew.c \
       ft_lstsize.c \
       $(PRINTF_DIR)/ft_printf.c \
       $(PRINTF_DIR)/ft_printf_fonction.c \
       $(PRINTF_DIR)/ft_printf_fonction_2.c \
       $(GNL_DIR)/get_next_line.c \
       $(GNL_DIR)/get_next_line_utils.c
OBJDIR = object
OBJ_FILES = $(patsubst %.c,$(OBJDIR)/%.o,$(FSRC))

#-----------------------RULE-----------------------#

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
