# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 16:11:10 by acoudouy          #+#    #+#              #
#    Updated: 2020/02/12 10:19:51 by acoudouy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=   cub3D
LIBFT		=   ./libft/libft.a
DIR_LIBFT	=   ./libft
INC			=   ./include 					\
				./libft
SRC_PATH 	=   ./src
SRC_NAME 	=	check_game.c				\
				check_map.c					\
				compute_ray.c				\
				destroy.c					\
				draw_wall.c					\
				find_intersection.c			\
				initialisation.c			\
				main.c						\
				movement_player.c			\
				open_file.c					\
				put_sprite.c				\
				read_map.c					\
				screen_bmp.c				\
				screen_bmp2.c				\
				sprites.c					\
				take_texture.c				\
				utils.c						\
				wall_limit.c
SRC = 			$(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_PATH	= ./obj
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ 		= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror
MFLAGS      = -lmlx -framework OpenGL -framework AppKit

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -s bonus -C $(DIR_LIBFT)
	make -s clean -C $(DIR_LIBFT)
	gcc $(CFLAGS) -o ${NAME} $(MFLAGS) $(LIBFT) ${OBJ}

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) -o $@ -c $<

clean:		
			rm -f $(OBJ)
			make -s clean -C $(DIR_LIBFT)

fclean:		clean
			@rm -f $(NAME)
			make -s fclean -C $(DIR_LIBFT)

re:			fclean all

.PHONY:		clean fclean all re
