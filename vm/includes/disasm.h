
#ifndef DISASM_H
# define DISASM_H

# include "vis.h"

typedef struct	s_disasm
{
	uint8_t			code;
	uint8_t			args[3];
	int				value[3];
	unsigned char	*arena;
	unsigned char	*bogie;
}				t_disasm;

size_t			len_num(int num);
int				from_int_to_char(int n, char **s, int i);
int				arguments_value(t_disasm *s, unsigned char *champ, int i);
int				add_dir_ind(t_disasm *s, char **str, int i, int j);
int				add_reg(t_disasm *s, char **str, int i, int j);

#endif
