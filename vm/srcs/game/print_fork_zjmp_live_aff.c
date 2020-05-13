#include "vm.h"

void	print_v_4_live(t_corewar *corewar, t_parse_args *arg_val,
					const char *cmd)
{
	printf("P%5d | %s %d\n",
		   corewar->carriages->id, cmd, arg_val->val[0]);
	fprintf(file, "P%5d | %s %d\n",
			corewar->carriages->id, cmd, arg_val->val[0]);
}

void	print_v_4_nfork(t_corewar *corewar, t_parse_args *arg_val,
					   const char *cmd)
{
	printf("P%5d | %s %d (%ld)\n",
		corewar->carriages->id,
		   cmd,
		(int16_t)arg_val->val[0],
		corewar->carriages->op_pos + (int16_t)arg_val->val[0] % IDX_MOD - corewar->arena);
	fprintf(file, "P%5d | %s %d (%ld)\n",
		corewar->carriages->id,
			cmd,
		(int16_t)arg_val->val[0],
		corewar->carriages->op_pos + (int16_t)arg_val->val[0] % IDX_MOD - corewar->arena);
}

void	print_v_4_lfork(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd)
{
	printf("P%5d | %s %d (%ld)\n",
		   corewar->carriages->id,
		   cmd,
		   (int16_t)arg_val->val[0],
		   corewar->carriages->op_pos + (int16_t)arg_val->val[0] - corewar->arena);
	fprintf(file, "P%5d | %s %d (%ld)\n",
			corewar->carriages->id,
			cmd,
			(int16_t)arg_val->val[0],
			corewar->carriages->op_pos + (int16_t)arg_val->val[0] - corewar->arena);
}

void	print_v_4_zjmp(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd)
{
	printf("P%5d | %s %d ",
		   corewar->carriages->id,
		   cmd,
		   (int16_t)arg_val->val[0]);
	fprintf(file, "P%5d | %s %d ",
			corewar->carriages->id,
			cmd,
			(int16_t)arg_val->val[0]);
}

void	print_v_4_aff(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd)
{
	printf("%s %c\n",
		   cmd, (char)corewar->carriages->reg[arg_val->val[0] - 1]);
	fprintf(file, "%s %c\n",
			cmd, (char)corewar->carriages->reg[arg_val->val[0] - 1]);
}
