#Compiler Options
#C_FLAGS =  -Wall -Wextra -Werror
C_FLAGS =  -Wall -Wextra
#Filenames
LIBFT_DIR := libft/
NAME:= lem-in
LEM_IN:= input.c error_management.c graph.c lem-in.c\
            tests.c graph2.c ssp_finder.c queue.c all_disjoint_paths.c

OBJECTS_LEM_IN := $(LEM_IN:.c=.o)
#HEADER = libft/libft.h

all: $(NAME)
$(NAME): $(OBJECTS_LEM_IN)
	make -C $(LIBFT_DIR)
	gcc -o $(NAME) $(OBJECTS_LEM_IN) -L$(LIBFT_DIR) -lft
$(OBJECTS_LEM_IN): %.o: %.c
	gcc $(C_FLAGS) -o $@ -c $<

clean:
	make clean -C $(LIBFT_DIR)
	/bin/rm -f $(OBJECTS_LEM_IN)
fclean: clean
	make fclean -C $(LIBFT_DIR)
	/bin/rm -f $(NAME)
	/bin/rm -f libft.a
re: fclean all