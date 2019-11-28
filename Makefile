# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 09:15:24 by acoudouy          #+#    #+#              #
#    Updated: 2019/11/25 17:12:31 by acoudouy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
LIBFT		= libft.a
DIR_LIBFT	= ./libft/
CFLAGS		= -Wall -Werror -Wextra -I. -c
FILES		= ft_argintotab.c \
				ft_argintotab_2.c \
				ft_argintotab_3.c \
				ft_check.c \
				ft_check2.c \
				ft_check_miniflag.c \
				ft_padding.c \
				ft_padding2.c \
				ft_precision.c \
				ft_print_separated.c \
				ft_print_separated2.c \
				ft_printf.c \
				ft_size.c \
				ft_toscreen.c \

OBJ			= $(FILES:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

.c.o:	
			cc $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): 		$(OBJ) ft_printf.h
				make -C $(DIR_LIBFT)
				cp $(DIR_LIBFT)$(LIBFT) ./$(NAME)
				ar rcs $(NAME) $(OBJ)
				/bin/rm -f $(LIBFT)
				ranlib $(NAME)

all:		$(NAME)

clean:		
			rm -f $(OBJ)
			make clean -C $(DIR_LIBFT)

fclean:		clean
			rm -f $(NAME)
			make fclean -C $(DIR_LIBFT)

re:			fclean all

.PHONY:		clean fclean all re
