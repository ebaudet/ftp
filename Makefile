# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/14 12:35:00 by ebaudet           #+#    #+#              #
#    Updated: 2014/05/14 13:22:24 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ftp

SERVEUR	= serveur
F_SRV	= serveur.c
SRC_SRV	= $(addprefix srcs/, $(F_SRV))
OBJ_SRV	= $(SRC_SRV:srcs/%.c=.obj/%.o)

CLIENT	= client
F_CLT	= client.c
SRC_CLT	= $(addprefix srcs/, $(F_CLT))
OBJ_CLT	= $(SRC_CLT:srcs/%.c=.obj/%.o)

INC		= -I includes -I libft/includes
FLAGS	= -Wall -Wextra -Werror
LIB		= -L libft -lft
CC		= gcc

all: $(NAME)

$(NAME): $(SERVEUR) $(CLIENT)

$(SERVEUR): make_libft $(OBJ_SRV)
	$(CC) $(FLAGS) $(OBJ_SRV) -o $(SERVEUR) $(INC) $(LIB)

$(CLIENT): make_libft $(OBJ_CLT)
	$(CC) $(FLAGS) $(OBJ_CLT) -o $(CLIENT) $(INC) $(LIB)

.obj/%.o: srcs/%.c
	@mkdir -p .obj
	$(CC) -c $< -o $@ $(FLAGS) $(INC)

make_libft:
	@echo "Compilation de la libft :"
	@make -C libft

clean:
	rm -rf .obj

fclean: clean
	rm -f $(OTOOL) $(NM)

re: fclean all

gdb: make_libft
	cc -g $(FLAGS) $(SRC_SRV) -o $(SERVEUR) $(INC) $(LIB)
	cc -g $(FLAGS) $(SRC_CLT) -o $(CLIENT) $(INC) $(LIB)

.PHONY: all clean fclean re gdb