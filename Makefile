#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pacovali <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/01 00:00:42 by pacovali      #+#    #+#                  #
#    Updated: 2019/01/01 00:01:42 by pacovali      ########   odam.nl          #
#                                                                              #
#******************************************************************************#

NAME = lem-in
SRCS = assign_distance.c assign_paths.c clean_map.c clean_paths.c \
crossing_paths.c distinct_paths.c main_utils.c main.c overlaying_paths.c \
run_ants.c set_map.c
MKOBJ = @gcc -c -Wall -Wextra -Werror
HDRS = -I libft/
OBJS = assign_distance.o assign_paths.o clean_map.o clean_paths.o \
crossing_paths.o distinct_paths.o main_utils.o main.o overlaying_paths.o \
run_ants.o set_map.o
LFT = libft/libftprintf.a
MKEXE = @gcc -o

all: $(NAME)
$(NAME):
	@make -C libft
	$(MKOBJ) $(SRCS) $(HDRS) -I.
	$(MKEXE) $(NAME) $(OBJS) $(LFT)

clean:
	@make -C libft clean
	@rm -f $(OBJS) *~

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all
