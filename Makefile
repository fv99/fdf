# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:12:49 by fvonsovs          #+#    #+#              #
#    Updated: 2023/03/15 12:53:21 by fvonsovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
NAME		=	fdf
SRCS		=	fdf.c fdf_map_parser.c fdf_map_utils.c fdf_draw_utils.c
OBJS		=	${SRCS:.c=.o}
LIBC		=	ar -cvq
RM			=	rm -f
LIBFT		=	./libft/libft.a
MINILIBX	=	./minilibx-linux/libmlx.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I. -I./libft -I/usr/include -I./minilibx-linux -O3

all: $(NAME)

$(NAME): ${OBJS}
	make -C ./libft
	make -C ./minilibx-linux
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${MINILIBX} -L/usr/lib -lm -lXext -lX11

clean: 
	${MAKE} clean -C ./libft
	${MAKE} clean -C ./minilibx-linux
	${RM} ${OBJS}

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
