# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmakino <hmakino@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/03 05:02:19 by hmakino           #+#    #+#              #
#    Updated: 2022/06/14 00:56:33 by hmakino          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftgnl.a

SRCS		=	get_next_line.c \
				get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
