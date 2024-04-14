# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arturo <arturo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 03:26:57 by artclave          #+#    #+#              #
#    Updated: 2024/04/15 04:09:19 by arturo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=address
SRC_DIR = srcs
OBJ_DIR = objs
LIB_DIR = libs
INCLUDES = -Iincludes -I$(LIB_DIR)/includes
SRCS = $(addprefix $(SRC_DIR)/, libft.c dinner.c death.c main.c mutexes.c parsing.c threads.c time.c utils.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Add the header file as a dependency for the target
$(NAME): $(OBJS) includes/philosophers.h
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all:
	make

clean:
	rm -rf $(OBJ_DIR)/*.o

fclean: clean
	rm -rf $(OBJ_DIR)/*.o
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
