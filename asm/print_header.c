

#include "libft.h"
#include "asm_dasha.h"
#include "options.h"


void	print_header(int fd, header_t *header)
{
	unsigned char num[4];

	num[3] = header->magic;
	num[2] = header->magic >> 8;
	num[1] = header->magic >> 16;
	num[0] = header->magic >> 24;
	write(fd, &num, 4);
	ft_bzero(num, 4);
	write(fd, &num, 4);
	*(uint32_t*)num = header->magic;
	write(fd, &num, 4);
//	write(fd, &header->prog_name, 6);
//	write(fd, "0000 0000", 4);
//	write(fd, &header->prog_size, 4);
}

