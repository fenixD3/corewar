
#include "asm_dasha.h"

int	token_exit(char *error, u_int32_t row, u_int32_t column)
{
	if (error)
		printf("%s, [row: %d, column: %d]\n", error, row, column);
	exit(1);
	return (0);
}
