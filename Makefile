# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:12:49 by fvonsovs          #+#    #+#              #
#    Updated: 2023/03/06 15:16:38 by fvonsovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
NAME		=	pipex
SRCS		=	main.c pipex.c pipex_utils.c
INCS		=	pipex.h
OBJS		=	${SRCS:.c=.o}
LIBC		=	ar -cvq
RM			=	rm -f
LIBFT		=	./libft/libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I. -I./libft -I/usr/include -Imlx_linux -O3

all: $(NAME)

$(NAME): ${OBJS}
	make -C ./libft
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

clean: 
	${MAKE} clean -C ./libft
	${RM} ${OBJS}

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
