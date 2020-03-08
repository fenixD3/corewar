

#include "libft.h"
#include "asm_dasha.h"
#include "options.h"


void    print_reverse(int fd, u_int8_t byte, u_int32_t *num)
{
	while (byte--)
		write(fd, &((u_int8_t*)num)[byte], 1);
}

void	print_header(int fd, header_t *header)
{
	int nullo;

	print_reverse(fd, 4, &header->magic);
	write(fd, &header->prog_name, PROG_NAME_LENGTH);
	nullo = 0;
	write(fd, &nullo, 4);
	print_reverse(fd, 4, &header->prog_size);
	write(fd, &header->comment, COMMENT_LENGTH);
}

