#include "vm.h"

unsigned char	*do_steps(unsigned char *start, int step, unsigned char *arena)
{

	if (start + step > arena + MEM_SIZE - 1)
		start = arena + (MEM_SIZE - (start + step - arena));
	else
		start += step;
	return (start);
}

short	reverse_vm_short_bytes(unsigned short *num_to_rev)
{
	unsigned short	rev;
	unsigned short	byte;
	unsigned short	i;

	rev = 0;
	i = 0;
	while (i < 16)
	{
		byte = *num_to_rev >> i & 0xFFu;
		rev |= byte << (16u - 8u - i);
		i += 8;
	}
	return ((short)rev);
}

int		reverse_vm_int_bytes(unsigned int *num_to_rev)
{
	unsigned int	rev;
	unsigned int	byte;
	unsigned int	i;

	rev = 0;
	i = 0;
	while (i < 32)
	{
		byte = *num_to_rev >> i & 0xFFu;
		rev |= byte << (32u - 8u - i);
		i += 8;
	}
	return ((int)rev);
}
