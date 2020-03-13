#include "vm.h"

unsigned char	*do_steps(unsigned char *start, char step, unsigned char *arena)
{

	if (start + step > arena + MEM_SIZE - 1)
		start = arena + (MEM_SIZE - (start + step - arena));
	else
		start += step;
	return (start);
}
