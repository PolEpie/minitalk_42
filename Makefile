# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pepie <pepie@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 00:50:04 by pepie             #+#    #+#              #
#    Updated: 2024/03/19 14:27:16 by pepie            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT		=	client
SERVER		=	server
LIBFT		=	libft/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)

CC			=	cc
INCLUDE 	=	./includes/
INCLUDE_LIBFT = $(addprefix $(LIBFT), includes/)
CFLAGS		=	-Wall -Werror -Wextra -g -I$(INCLUDE) -I$(INCLUDE_LIBFT)
RM			=	rm -f
OBJ_DIR		=	objs
SRCS_CLIENT		=	srcs/client/main.c
OBJS_CLIENT		=	$(SRCS_CLIENT:/%.c=%.o)

SRCS_SERVER		=	srcs/server/main.c
OBJS_SERVER		=	$(SRCS_SERVER:/%.c=%.o)

all:			client server

client:			$(OBJS_CLIENT) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFT) -lft -o $(CLIENT)
				@echo "Linked into executable \033[0;32m$(CLIENT)\033[0m."

server:			$(OBJS_SERVER) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJS_SERVER) -L$(LIBFT) -lft -o $(SERVER)
				@echo "Linked into executable \033[0;32m$(SERVER)\033[0m."

test:			$(NAME)
				@./$(NAME) 99 0 25 -38 10 7 42


$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."

bonus:			all

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
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."

fclean:			localclean
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full clean libft."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."
				@$(RM) $(NAME)
				@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus 