# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/03 05:02:19 by hmakino           #+#    #+#              #
#    Updated: 2022/12/09 18:25:32 by hiroaki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftgnl.a
CFLAGS		=	-Wall -Wextra -Werror -I$(INC)

SRCS		=	get_next_line.c \
				get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)
INC			=	../../include

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
