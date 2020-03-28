LEMIN		=	lem-in
LIBFT		=	libft/libft.a

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

INCLUDES = $(addprefix includes/,\
                        lem_in.h\
                        graph.h\
                        path.h\
                        queue.h)

SRC = $(addprefix src/,\
                    input.c\
                    error_management.c\
                    graph.c\
                    lem_in.c\
                    graph2.c\
                    ssp_finder.c\
                    queue.c\
                    all_disjoint_paths.c\
                    graph3.c\
                    paths.c\
                    mergesort.c\
                    ants.c\
                    output.c\
                    parser.c\
                    algorithm.c\
                    graph4.c\
                    input2.c\
                    all_disjoint_paths2.c)

OBJ	= $(patsubst src/%.c, obj/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(LEMIN) $(VERIFIER)

clean:
	 rm -f $(OBJ)
	 make clean -sC libft/

fclean: clean
	 rm -rf obj/
	 rm -f $(LEMIN)
	 make fclean -sC libft/

re: fclean all

$(LEMIN): $(LIBFT) $(OBJ)
	 mkdir -p obj/
	 $(CC) -o $(LEMIN) $(OBJ) $(LIBFT)

$(LIBFT):
	 make -sC libft/

obj/%.o: src/%.c $(INCLUDES) libft/libft.h
	 mkdir -p $(dir $@)
	 $(CC) $(CFLAGS) -o $@ -c $< -I includes/ -I libft/


