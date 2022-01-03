# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 15:51:21 by qrolande          #+#    #+#              #
#    Updated: 2022/01/03 20:21:38 by qrolande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

SRCS  		=	srcs/main.c \
				srcs/begin.c \
				srcs/if_space.c \
				srcs/env_parser.c \
				srcs/prepare_cmd.c
						
OBJS		=	${SRCS:.c=.o}

LINE		=	-lreadline

CC			= 	gcc -g

RM			= 	rm -f

CFLAGS		= 	-Wall -Wextra -Werror

INCLUDES	= 	./includes/minishell.h

LIBFT		=	./libft/libft.a

%.o : %.c	$(INCLUDES)
			${CC} ${CFLAGS} -c $< -I ${INCLUDES} -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDES)
			${MAKE} -C ./libft
			${MAKE} bonus -C ./libft
			${CC} ${LINE} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
			@echo "Make done"

clean:		
			@${MAKE} clean -C ./libft
			@${RM} ${OBJS}
			@echo "Make clean done" 

fclean:		
			@${MAKE} fclean -C ./libft
			@${RM} ${OBJS}
			@${RM} ${NAME}
			@echo "Make fclean done"

re:			fclean all

.PHONY:		all clean fclean re