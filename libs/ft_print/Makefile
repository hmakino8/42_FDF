# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/03 05:02:19 by hmakino           #+#    #+#              #
#    Updated: 2022/11/19 02:43:14 by hiroaki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprint.a

PRINT		=	ft_print.c \
				init.c \
				scrape.c \
				utils.c \
				output.c

OBJS		=	$(PRINT:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus
