# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 20:58:46 by rkhakimu          #+#    #+#              #
#    Updated: 2024/08/22 20:58:49 by rkhakimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isascii.c \
	  ft_memcpy.c \
	  ft_strlcat.c \
	  ft_strrchr.c \
	  ft_bzero.c \
	  ft_isdigit.c \
	  ft_memmove.c \
	  ft_strlcpy.c \
	  ft_tolower.c \
	  ft_calloc.c \
	  ft_isprint.c \
	  ft_memset.c \
	  ft_strlen.c \
	  ft_toupper.c \
	  ft_isalnum.c \
	  ft_memchr.c \
	  ft_strchr.c \
	  ft_strncmp.c \
	  ft_isalpha.c \
	  ft_memcmp.c \
	  ft_strdup.c \
	  ft_strnstr.c \
	  ft_atoi.c \
	  ft_calloc.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_printchar.c \
	  ft_printf.c \
	  ft_printhex.c \
	  ft_printhex_ptr.c \
	  ft_printnbr.c \
	  ft_printstr.c \
	  ft_printunbr.c \
	  get_next_line_bonus.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  get_next_line_utils_bonus.c \


SRC_BONUS = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
OBJ = $(SRC:.c=.o)
OBJ_bonus = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "libft.a compiled successfully"

bonus: $(OBJ) $(OBJ_BONUS)
	@ar rcs $(NAME) $^
	@echo "libft with bonus compiled successfully"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -f $(OBJ) $(OBJ_BONUS) 
	@echo "Libft object files cleaned successfully"

fclean: clean
	@rm -f $(NAME)
	@echo "Libft fully cleaned"

re: fclean all

.PHONY: all clean fclean re bonus
