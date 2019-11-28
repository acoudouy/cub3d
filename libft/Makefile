# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 09:15:24 by acoudouy          #+#    #+#              #
#    Updated: 2019/11/21 19:16:41 by acoudouy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CFLAGS		= -Wall -Werror -Wextra -I. -c
FILES		= ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_strlen.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strnstr.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isprint.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_isascii.c \
				ft_atoi.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_strmapi.c \
				ft_split.c \
				ft_itoa.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putnbr_unsigned_fd.c \
				ft_calloc.c \
				ft_strdup.c \

FILES2		=	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \

OBJ			= $(FILES:.c=.o)

OBJ2		= $(FILES2:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

.c.o:	
			cc $(CFLAGS) -c $< -o $(<:.c=.o)


$(NAME):	$(OBJ) libft.h
			ar rcs $(NAME) $(OBJ)

all:		$(NAME)

clean:		
			rm -f $(OBJ) $(OBJ2)

fclean:		clean
			rm -f ${NAME}

re:			fclean all

bonus:		${OBJ} ${OBJ2}
			ar rcs ${NAME} ${OBJ} ${OBJ2}

.PHONY:		clean fclean all re
