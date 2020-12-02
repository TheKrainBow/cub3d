SRCS_ALGO	=	srcs/algo/math.c						\
				srcs/algo/raycasting.c					\
				srcs/algo/wall.c						\
				srcs/algo/sprite.c

SRCS_DRAW	=	srcs/draw/draw_color.c					\
				srcs/draw/draw_hud.c					\
				srcs/draw/draw_objs.c					\
				srcs/draw/draw_wall.c					\
				srcs/draw/draw_map.c					\
				srcs/draw/draw_shapes.c

SRCS_INIT	=	srcs/initialization/init_mlx.c			\
				srcs/initialization/init_gun.c

SRCS_PARS	=	srcs/parsing/parsing.c					\
				srcs/parsing/parsing1.c					\
				srcs/parsing/parsing2.c					\
				srcs/parsing/parsing3.c					\
				srcs/parsing/parsing4.c					\
				srcs/parsing/parsing_utils.c

SRCS_UTIL	=	srcs/utils/hook.c						\
				srcs/utils/utils.c						\
				srcs/utils/utils2.c						\
				srcs/utils/main.c						\
				srcs/utils/move_player.c				\
				srcs/utils/save.c						\
				srcs/utils/ft_itoa.c					\

SRCS_GNL	=	get_next_line/get_next_line.c			\
				get_next_line/get_next_line_utils.c

INCLUDES	=	-Isrcs/algo								\
				-Isrcs/draw								\
				-Isrcs/initialization					\
				-Isrcs/parsing							\
				-Isrcs/utils							\
				-Iincludes


SRCS		=	$(SRCS_GNL) $(SRCS_ALGO) $(SRCS_DRAW) $(SRCS_INIT) $(SRCS_PARS) $(SRCS_UTIL)
OBJS		=	$(SRCS:.c=.o)

CC			=	@clang
RM			=	@rm -f
NAME		=	Cub3D

LD_FLAGS	=	-Lmlx -lbsd -lmlx -lXext -lX11 -lm -g
FLAGS		=	-Wall -Werror -Wextra $(INCLUDES)

.c.o:
				$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME):		start_message $(OBJS) start_link
				$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)
				@echo "\033[1;31mCub3D\033[0m is ready to use!"

all:			$(NAME)

clean:
				@echo "\033[0;33mCleaning \033[1;31mCub3D\033[0;33m's objects\033[0m"
				$(RM) $(OBJS)

fclean:			clean
				@echo "\033[0;33mRemoving \033[1;31mCub3D\033[0m"
				$(RM) $(NAME)

start_message:
				@echo "\033[0;31mMaking \033[1;31mCub3D"
				@echo "\033[0;32mCompiling objects\033[0m"

start_link:
				@echo "\033[0;32mLinking all objects\033[0m"

re:				fclean all

.PHONY:			all clean fclean re