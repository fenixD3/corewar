//
// Created by Mort Deanne on 07/02/2020.
//

#include <stdio.h>
#include <libft/libft.h>
#include <fcntl.h>
#include "file_to_list.h"
#include "asm.h"
#include "op.h"

//int main(int ac, char **av)
//{
//	int fd;
//	t_fline *flst;
//
//	if (ac < 2)
//		go_exit("Give me file, bitch!");
//
//	if (!(fd = open(av[1], O_RDONLY)))
//		go_exit("Open file error");
//
//	flst = file_to_list(fd);
//
//	char *line = flst->next->line;
//	printf("%s\n\n", line);
//	char **arrptr;
//	if (!(arrptr = fast_strsplit(line, DELIMITERS, COMMENTS, malloc)))
//		return (2);
//	while (*arrptr)
//	{
//		printf("%s\n", *arrptr);
//		arrptr++;
//	}
//	return (0);
//}

int main(void)
{
	int *ptr;
	int *tmp;

	ptr = (int*)ml_malloc(sizeof(int), 1);
	*ptr = 1;
	ptr = (int*)ml_malloc(sizeof(int), 5);
	*ptr = 5;
	ptr = (int*)ml_malloc(sizeof(int), 3);
	*ptr = 3;
	ptr = (int*)ml_malloc(sizeof(int), 8);
	*ptr = 8;
	ptr = (int*)ml_malloc(sizeof(int), 1);
	*ptr = 11;
	ptr = (int*)ml_malloc(sizeof(int), 5);
	*ptr = 55;
	tmp = ptr;
	ptr = (int*)ml_malloc(sizeof(int), 3);
	*ptr = 33;
	ptr = (int*)ml_malloc(sizeof(int), 8);
	*ptr = 88;
	ptr = (int*)ml_malloc(sizeof(int), 3);
	*ptr = 333;
	ml_free(tmp, 5);
	ml_free_list(8);
	ml_free_list(8);
	ml_free(tmp, 3);

	return (0);
}
