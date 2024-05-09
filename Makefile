# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 15:05:47 by ana-cast          #+#    #+#              #
#    Updated: 2024/05/08 15:16:50 by ana-cast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                               COMPILATION INFO                             ##
################################################################################

NAME = minishell
CC_FLAGS = gcc -Wall -Wextra -Werror
RM = rm -f
MINISHELL = include/
INCLUDE = -L ./lib/libft -lft
DEPS = -I include -I $(LIBFT)/include

################################################################################
##                              SOURCES AND OBJECTS                           ##
################################################################################

#SRC = \

#OBJECTS = $(SRC:.c=.o)

#BONUS_SR = \
	
#BONUS_OB = $(BONUS_SR:.c=.o)

################################################################################
##                                     RULES                                  ##
################################################################################

all : libft $(NAME)

libft :
	@make -C $(LIBFT)

$(NAME) : line $(OBJECTS)
	@echo "✦ ---------------------- ✦$(END)"
	@$(CC_FLAGS) $(OBJECTS) $(INCLUDE) -o $(NAME)

bonus : all line $(BONUS_OB)
	@echo "✦ ---------------------- ✦$(END)"
	@$(CC_FLAGS) $(BONUS_OB) $(INCLUDE) -o $(NAME)

%.o : %.c $(MINISHELL)
	@$(CC_FLAGS) -c $< -o $@ $(DEPS)
	@echo "$(GREEN)  ✓ Compiled: $(notdir $<)"

line :
	@echo "$(GREEN) $(BOLD)"
	@echo "    COMPILING MINISHELL...$(END) $(GREEN)"
	@echo "✦ ---------------------- ✦"

clean :
	@printf "\n$(YELLOW) 🗑   Removing objects$(END)"
	@$(RM) $(OBJECTS) $(BONUS_OB)
	@echo "$(GREEN)\r  ✓  $(RED)Removed  objects from $(NAME) $(END)"
	@make clean -C $(LIBFT)

fclean: clean
	@printf "$(YELLOW) 🗑   Removing $(NAME) $(END)"
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)
	@echo "$(GREEN)\r  ✓  $(RED)Removed  $(NAME) $(END)\n"

re :
	@$(MAKE) fclean
	@clear
	@$(MAKE) all

.PHONY: all bonus clean fclean re