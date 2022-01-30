# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 15:51:21 by qrolande          #+#    #+#              #
#    Updated: 2022/01/30 06:49:39 by qrolande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

SRCS  		=	srcs/main.c \
				srcs/begin.c \
				srcs/types.c \
				srcs/syntax.c \
				srcs/heredoc.c \
				srcs/signals.c \
				srcs/redirect.c \
				srcs/pipe_magic.c \
				srcs/env_parser.c \
				srcs/parser_cmd.c \
				srcs/env_parser2.c \
				srcs/prepare_cmd.c \
				srcs/cmd_executor.c \
				srcs/cleaning_company.c \
				srcs/two_dimension_check.c \
				functions/export_without_param.c \
				functions/export_with_param.c \
				functions/utils.c \
				functions/unset.c \
				functions/echo.c \
				functions/exit.c \
				functions/pwd.c \
				functions/env.c \
				functions/cd.c
						
OBJS		=	${SRCS:.c=.o}

LINE		=	-lreadline -I/Users/${USER}/.brew/opt/readline/include -L/Users/${USER}/.brew/opt/readline/lib/

CC			= 	gcc -g

RM			= 	rm -f

CFLAGS		= 	

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