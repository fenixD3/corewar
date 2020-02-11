//
// Created by Mort Deanne on 07/02/2020.
//

#include <stdio.h>
#include <libft/libft.h>
#include <fcntl.h>
#include "file_to_list.h"
#include "asm.h"
#include "op.h"

int main(int ac, char **av)
{
	int fd;
	t_fline *flst;

	if (ac < 2)
		go_exit("Give me file, bitch!");

	if (!(fd = open(av[1], O_RDONLY)))
		go_exit("Open file error");

	flst = file_to_list(fd);
	printf("%s\n", flst->next->line);

	char **arrptr = fast_strsplit(flst->next->line, DELIMITERS, COMMENTS);
	return (0);
}