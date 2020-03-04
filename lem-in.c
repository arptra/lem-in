#include "lem-in.h"

int	main(int argc, char **argv)
{
	int fd;
	
	fd = open(argv[1], O_RDONLY);
	test();
	fill_graph(fd);
	return (0);
}