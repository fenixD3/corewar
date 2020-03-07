

#include "libft.h"
#include "asm_dasha.h"
#include "options.h"


void	print_header(int fd, header_t *header)
{
	unsigned char num[4];
	unsigned char name[6];

//	num[3] = header->magic;
//	num[2] = header->magic >> 8;
//	num[1] = header->magic >> 16;
//	num[0] = header->magic >> 24;
//	write(fd, &num, 4);
//	ft_bzero(num, 4);
//	write(fd, &num, 4);
//	*(uint32_t*)num = header->magic;
//	write(fd, &num, 4);
	name[0] = header->prog_name[5];
	name[1] = header->prog_name[4];
	name[2] = header->prog_name[3];
	name[3] = header->prog_name[2];
	name[4] = header->prog_name[1];
	name[5] = header->prog_name[0];
	write(fd, &name, 6);
//	write(fd, "0000 0000", 4);
//	write(fd, &header->prog_size, 4);
}

