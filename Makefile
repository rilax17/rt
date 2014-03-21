# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/16 21:15:11 by nyguel            #+#    #+#              #
#    Updated: 2014/02/16 21:15:32 by nyguel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt
SRCS = main.c\
	set_param.c get_data.c ray_cast.c base_ch.c get_color_obj.c\
	calc_li.c view.c set_obj.c fonctions.c\
	inter_li.c inter_trans.c inter_pl.c inter_sph.c inter_cy.c inter_co.c\
	ft_inside_cocy.c ft_inter.c ft_normale.c ft_normale2.c ft_shade.c\
	ft_color.c ft.c ft_threads.c \
	rt_get_scene.c rt_get.c rt_tools.c

LIBS = 	-L/usr/X11/lib -lmlx -lXext -lX11 -lpthread\
		-Llibs/libprt -lprt\
		-Llibs/libft -lft\
		-Llibs/libgnl -lgnl
		
		
HPATH = -Iincludes\
		-Ilibs/libprt/includes\
		-Ilibs/libgnl/includes\
		-Ilibs/libft/includes\
		-I/usr/X11/include

CC = clang
CFLAGS = -Werror -Wall -Wextra -g
RM = rm -rf
SRCDIR = srcs
OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# COLORS
RESET=		\033[0m
DARK=		\033[1;32m
RED=		\033[31m
GREEN=		\033[32m
YELLOW=		\033[33m
BLUE=		\033[34m
MAGENTA=	\033[35m
CYAN=		\033[36m
WHITE=		\033[37m
BOLDBLACK=	\033[1m\033[30m
BOLDRED=	\033[1m\033[31m
BOLDWHITE=	\033[1m\033[37m

# START RULES
.PHONY: all clean fclean re

all: libdep $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)building $(NAME)$(RED)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HPATH) -o $(NAME)
	@echo "$(RESET)$(GREEN)ready to rumble!$(RESET)"

$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.c)
	@mkdir -p $(OBJDIR)
	@$(CC) $(HPATH) -o $@ -c $^

libdep:
	@make -C libs/libprt
	@make -C libs/libgnl
	@make -C libs/libft

libdepclean:
	@make -C libs/libprt fclean
	@make -C libs/libgnl fclean
	@make -C libs/libft fclean

clean:
	@echo "$(YELLOW)removing $(OBJDIR)...$(RESET)"
	@$(RM) $(OBJDIR)

fclean: clean #libdepclean
	@echo "$(YELLOW)removing $(NAME) and $(LIBA)...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

# DO NOT DELETE THIS LINE -- make depends on it


