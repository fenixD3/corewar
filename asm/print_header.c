

#include "libft.h"
#include "asm_dasha.h"
#include "options.h"


void	print_header(int fd, header_t *header)
{
	write(fd, &header->magic, 4);
}

