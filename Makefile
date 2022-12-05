# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 03:03:24 by hiroaki           #+#    #+#              #
#    Updated: 2022/12/05 21:06:57 by hiroaki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fdf
FLAGS			=	-Wall -Wextra -Werror #-g -fsanitize=address -fsanitize=integer -fsanitize=undefined

SRCS			=	main/main.c \
					init/init.c \
					parse/get_matrix.c \
					parse/get_color_code.c \
					parse/get_coord.c \
					parse/parse_coord_info.c \
					color/color.c \
					render/draw.c \
					render/render.c \
					render/menu.c \
					key/key_hook.c \
					key/operation_key.c \
					exit/exit.c \
					exit/alloc.c \
					utils/ft_atoi_base.c \
					utils/ft_abs.c \
					utils/ft_max.c \
					utils/ft_min.c \
					utils/check.c

SRCS_PATH		= 	$(addprefix src/, $(SRCS))
OBJS_PATH		=	$(SRCS_PATH:%.c=%.o)

all: 			$(NAME)

$(NAME):		$(OBJS_PATH) $(LIBFT) $(PRINT) $(GNL)
				$(MAKE) -C libs/libft
				$(MAKE) -C libs/ft_print
				$(MAKE) -C libs/gnl
				$(MAKE) -C minilibx_macos
				$(CC) $(FLAGS) $(SRCS_PATH) $(LIBFT) $(PRINT) $(GNL) $(MLX) -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit  -o $(NAME)

LIBFT			=	libs/libft/libft.a
PRINT			=	libs/ft_print/libftprint.a
GNL				=	libs/gnl/libftgnl.a
MLX				=	minilibx_macos/libmlx.a

clean:
				$(MAKE) -C libs/libft clean
				$(MAKE) -C libs/ft_print clean
				$(MAKE) -C libs/gnl clean
				$(MAKE) -C minilibx_macos clean
				$(RM) $(OBJS_PATH)

fclean:			clean
				$(RM) $(LIBFT)
				$(RM) $(PRINT)
				$(RM) $(GNL)
				$(RM) $(MLX)
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
