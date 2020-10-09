SRCS_ALGO	=		srcs/algo/math.c						\
				srcs/algo/raycasting.c					\
				srcs/algo/sprite.c

SRCS_DRAW	=		srcs/draw/draw_color.c					\
				srcs/draw/draw_hud.c					\
				srcs/draw/draw_objs.c					\
				srcs/draw/draw_shapes.c

SRCS_INIT	=		srcs/initialization/fill_walls.c		\
				srcs/initialization/init_mlx.c			\
				srcs/initialization/init_walls.c		\
				srcs/initialization/utils_walls.c

SRCS_PARS	=		srcs/parsing/parsing.c

SRCS_UTIL	=		srcs/utils/hook.c						\
					srcs/utils/utils.c						\
					srcs/utils/main.c

SRCS_GNL	=		get_next_line/get_next_line.c			\
					get_next_line/get_next_line_utils.c


SRCS		= ${SRCS_GNL} ${SRCS_ALGO} ${SRCS_DRAW} ${SRCS_INIT} ${SRCS_PARS} ${SRCS_UTIL}
OBJS		= ${SRCS:.c=.o}

CC			= clang
RM			= rm -f
NAME		= Cub3d

FLAGS_MLX	= -lbsd -lmlx -lXext -lX11 -lm
FLAGS		= -Wall -Werror -Wextra -Iincludes $(FLAGS_MLX) -g -O3 -o $(NAME)

.c.o:
			${CC} -c $< -o ${<:.c=.o} ${FLAGS}

all:		${SRCS}
			${CC} ${SRCS} ${FLAGS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re