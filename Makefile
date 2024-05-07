# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pepie <pepie@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 00:50:04 by pepie             #+#    #+#              #
#    Updated: 2024/05/07 10:54:25 by pepie            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT			=	client
SERVER			=	server
LIBFT			=	libft/
LIBFT_A			=	$(addprefix $(LIBFT), libft.a)

CC				=	cc
INCLUDE 		=	./includes/
INCLUDE_LIBFT 	= 	$(addprefix $(LIBFT), includes/)
CFLAGS			=	-Wall -Werror -Wextra -g -I$(INCLUDE) -I$(INCLUDE_LIBFT)
RM				=	rm -f
OBJ_DIR			=	objs
SRCS_CLIENT		=	srcs/client/main.c
OBJS_CLIENT		=	$(SRCS_CLIENT:/%.c=%.o)

SRCS_SERVER		=	srcs/server/main.c
OBJS_SERVER		=	$(SRCS_SERVER:/%.c=%.o)


SRCS_CLIENT_B	=	srcs/client/main_bonus.c
OBJS_CLIENT_B	=	$(SRCS_CLIENT:/%.c=%.o)

SRCS_SERVER_B	=	srcs/server/main_bonus.c
OBJS_SERVER_B	=	$(SRCS_SERVER:/%.c=%.o)

all:			client server

client:			$(OBJS_CLIENT) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFT) -lft -o $(CLIENT)
				@echo "Linked into executable \033[0;32m$(CLIENT)\033[0m."

server:			$(OBJS_SERVER) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJS_SERVER) -L$(LIBFT) -lft -o $(SERVER)
				@echo "Linked into executable \033[0;32m$(SERVER)\033[0m."

client_bonus:	$(OBJS_CLIENT_B) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJS_CLIENT_B) -L$(LIBFT) -lft -o $(CLIENT)
				@echo "Linked into executable \033[0;32m$(CLIENT)\033[0m."

server_bonus:	$(OBJS_SERVER_B) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJS_SERVER_B) -L$(LIBFT) -lft -o $(SERVER)
				@echo "Linked into executable \033[0;32m$(SERVER)\033[0m."

test:			$(NAME)
				@./$(NAME) 99 0 25 -38 10 7 42


$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."

bonus:			client_bonus server_bonus

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$(<:.c=.o)
				@echo "Compiling $<."

localclean:
				@$(RM) -rf $(OBJ_DIR)
				@mkdir $(OBJ_DIR)
				@echo "Removed object files."

clean:			localclean
				@$(MAKE) clean -s -C $(LIBFT)
				@echo "Clean libft."

fclean:			localclean
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full clean libft."
				@$(RM) $(NAME)
				@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus 