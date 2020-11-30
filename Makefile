SRCS_ALGO	=		srcs/algo/math.c						\
					srcs/algo/raycasting.c					\
					srcs/algo/wall.c						\
					srcs/algo/sprite.c

SRCS_DRAW	=		srcs/draw/draw_color.c					\
					srcs/draw/draw_hud.c					\
					srcs/draw/draw_objs.c					\
					srcs/draw/draw_wall.c					\
					srcs/draw/draw_map.c					\
					srcs/draw/draw_shapes.c

SRCS_INIT	=		srcs/initialization/init_mlx.c			\
					srcs/initialization/init_gun.c

SRCS_PARS	=		srcs/parsing/parsing.c					\
					srcs/parsing/parsing1.c					\
					srcs/parsing/parsing2.c					\
					srcs/parsing/parsing3.c					\
					srcs/parsing/parsing_utils.c

SRCS_UTIL	=		srcs/utils/hook.c						\
					srcs/utils/utils.c						\
					srcs/utils/utils2.c						\
					srcs/utils/main.c						\
					srcs/utils/save.c						\
					srcs/utils/ft_itoa.c					\

SRCS_GNL	=		get_next_line/get_next_line.c			\
					get_next_line/get_next_line_utils.c

INCLUDES	=		-Isrcs/algo								\
					-Isrcs/draw								\
					-Isrcs/initialization					\
					-Isrcs/parsing							\
					-Isrcs/utils							\
					-Iincludes


SRCS		= ${SRCS_GNL} ${SRCS_ALGO} ${SRCS_DRAW} ${SRCS_INIT} ${SRCS_PARS} ${SRCS_UTIL}
OBJS		= ${SRCS:.c=.o}

CC			= clang
RM			= rm -f
NAME		= Cub3d

FLAGS_MLX	= -lbsd -lmlx -lXext -lX11 -lm
FLAGS		= -Wall -Werror -Wextra ${INCLUDES} $(FLAGS_MLX) -g -O3 -o $(NAME)

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