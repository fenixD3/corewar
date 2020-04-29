#include "vm.h"

void    live(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	t_champion	*champ;

	if (!*head)
	    return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d\n",
			   corewar->carriages->id, "live", arg_val->val[0]);
		fprintf(file, "p%5d | %s %d\n",
			   corewar->carriages->id, "live", arg_val->val[0]);
	}
	corewar->carriages->is_live = 1;
	++corewar->game_param.live_period_cnt;
	corewar->carriages->cycle_when_live = corewar->game_param.cycles_aft_start;
	champ = corewar->champs;
	while (champ)
	{
		if (champ->num == -arg_val->val[0])
		{
			corewar->game_param.who_lst_live = -arg_val->val[0];
			if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 1) {
				printf("Player %d (%s) is said to be alive\n",
					   -arg_val->val[0], champ->file.header.prog_name);
				fprintf(file, "Player %d (%s) is said to be alive\n",
					   -arg_val->val[0], champ->file.header.prog_name);
			}
			break ;
		}
		champ = champ->next;
	}
}

void    ld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
    int		val;

    if (!*head)
        return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d r%d\n",
			   corewar->carriages->id, "ld", arg_val->val[0], arg_val->val[1]);
		fprintf(file, "p%5d | %s %d r%d\n",
				corewar->carriages->id, "ld", arg_val->val[0], arg_val->val[1]);
	}
    val = get_value_frm_arg(arg_val, 0, corewar, 1);
    corewar->carriages->reg[arg_val->val[1] - 1] = val;
    if (!val)
        corewar->carriages->carry = 1;
    else
        corewar->carriages->carry = 0;
}

void    ldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val_addr_1;
	int					val_addr_2;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf(
			"p%5d | %s %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n",
			corewar->carriages->id,
			"ldi",
			arg_val->val[0],
			arg_val->val[1],
			arg_val->val[2],
			arg_val->val[0],
			arg_val->val[1],
			arg_val->val[0] + arg_val->val[1],
			(val_addr_1 + val_addr_2) % IDX_MOD);
		fprintf(file,
				"p%5d | %s %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n",
				corewar->carriages->id,
				"ldi",
				arg_val->val[0],
				arg_val->val[1],
				arg_val->val[2],
				arg_val->val[0],
				arg_val->val[1],
				arg_val->val[0] + arg_val->val[1],
				(val_addr_1 + val_addr_2) % IDX_MOD);
	}
	corewar->carriages->reg[arg_val->val[2] - 1] = reverse_vm_bytes(do_steps(corewar->carriages->op_pos,
		(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena), 4, corewar->arena);
}

void    lld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d r%d\n",
			   corewar->carriages->id, "lld", arg_val->val[0], arg_val->val[1]);
		fprintf(file, "p%5d | %s %d r%d\n",
			   corewar->carriages->id, "lld", arg_val->val[0], arg_val->val[1]);
	}
	val = get_value_frm_arg(arg_val, 0, corewar, 0);
	corewar->carriages->reg[arg_val->val[1] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void    lldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val_addr_1;
	int					val_addr_2;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 0);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d %d r%d\n       | -> load from %d + %d = %d (with pc %d)\n",
			   corewar->carriages->id,
			   "lldi",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2],
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[0] + arg_val->val[1],
			   (val_addr_1 + val_addr_2));
		fprintf(file, "p%5d | %s %d %d r%d\n       | -> load from %d + %d = %d (with pc %d)\n",
				corewar->carriages->id,
				"lldi",
				arg_val->val[0],
				arg_val->val[1],
				arg_val->val[2],
				arg_val->val[0],
				arg_val->val[1],
				arg_val->val[0] + arg_val->val[1],
				(val_addr_1 + val_addr_2));
	}
	corewar->carriages->reg[arg_val->val[2] - 1] = reverse_vm_bytes(do_steps(corewar->carriages->op_pos,
		(val_addr_1 + val_addr_2), corewar->arena), 4, corewar->arena);
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	st(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val;
	unsigned char	*ind_pos;
	int				i;
	unsigned char	*val_ptr;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s r%d %d\n",
			   corewar->carriages->id, "st", arg_val->val[0], arg_val->val[1]);
		fprintf(file, "p%5d | %s r%d %d\n",
			   corewar->carriages->id, "st", arg_val->val[0], arg_val->val[1]);
	}
	val = corewar->carriages->reg[arg_val->code_args[0] - 1];
	if (arg_val->code_args[1] == REG_CODE)
		corewar->carriages->reg[arg_val->code_args[1] - 1] = val;
	else if (arg_val->code_args[1] == IND_CODE)
	{
		ind_pos = do_steps(corewar->carriages->op_pos,
				arg_val->val[1] % IDX_MOD, corewar->arena);
		i = 4;
		val_ptr = (unsigned char *)&val;
		while (--i >= 0)
		{
			*ind_pos = *(val_ptr + i);
			ind_pos = do_steps(ind_pos, 1, corewar->arena);
		}
	}
}

void	sti(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	unsigned char	*ind_pos;
	int				val_addr_1;
	int				val_addr_2;
	int				i;
	unsigned char	*val_ptr;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 1, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 2, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf(
			"p%5d | %s r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n",
			corewar->carriages->id,
			"sti",
			arg_val->val[0],
			arg_val->val[1],
			arg_val->val[2],
			arg_val->val[1],
			arg_val->val[2],
			arg_val->val[1] + arg_val->val[2],
			(val_addr_1 + val_addr_2) % IDX_MOD);
		fprintf(file,
				"p%5d | %s r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n",
				corewar->carriages->id,
				"sti",
				arg_val->val[0],
				arg_val->val[1],
				arg_val->val[2],
				arg_val->val[1],
				arg_val->val[2],
				arg_val->val[1] + arg_val->val[2],
				(val_addr_1 + val_addr_2) % IDX_MOD);
	}
	ind_pos = do_steps(corewar->carriages->op_pos,
			(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena);
	i = 4;
	val_ptr = (unsigned char *)&corewar->carriages->reg[arg_val->val[0] - 1];
	while (--i >= 0)
	{
		*ind_pos = *(val_ptr + i);
		ind_pos = do_steps(ind_pos, 1, corewar->arena);
	}
}

void	zjump(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d ",
			   corewar->carriages->id, "zjmp", arg_val->val[0]);
		fprintf(file, "p%5d | %s %d ",
			   corewar->carriages->id, "zjmp", arg_val->val[0]);
	}
	if (!corewar->carriages->carry || !*head)
	{
		if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
			printf("FAILED\n");
			fprintf(file, "FAILED\n");
		}
		return;
	}
	corewar->carriages->op_pos = do_steps(corewar->carriages->op_pos,
			arg_val->val[0] % IDX_MOD, corewar->arena);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("OK\n");
		fprintf(file, "OK\n");
	}
}

void	add(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s r%d r%d r%d\n",
			   corewar->carriages->id,
			   "add",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
		fprintf(file, "p%5d | %s r%d r%d r%d\n",
			   corewar->carriages->id,
			   "add",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
	}
	val = corewar->carriages->reg[arg_val->val[0] - 1] +
			corewar->carriages->reg[arg_val->val[1] - 1];
	corewar->carriages->reg[arg_val->val[2] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	sub(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s r%d r%d r%d\n",
			   corewar->carriages->id,
			   "sub",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
		fprintf(file, "p%5d | %s r%d r%d r%d\n",
			   corewar->carriages->id,
			   "sub",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
	}
	val = corewar->carriages->reg[arg_val->val[0] - 1] -
		  corewar->carriages->reg[arg_val->val[1] - 1];
	corewar->carriages->reg[arg_val->val[2] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	and(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "and",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
		fprintf(file, "p%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "and",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
	}
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 & val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	or(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "or",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
		fprintf(file, "p%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "or",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
	}
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 | val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	xor(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "xor",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
		fprintf(file, "p%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "xor",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
	}
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 ^ val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	aff(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("%s %c\n",
			   "Aff:", (char)corewar->carriages->reg[arg_val->val[0] - 1]);
		fprintf(file, "%s %c\n",
			   "Aff:", (char)corewar->carriages->reg[arg_val->val[0] - 1]);
	}
	if (!*head || !(corewar->flgs.set_flg & A_FLG))
		return ;
	ft_printf("%c\n",
			(char)corewar->carriages->reg[arg_val->val[0] - 1]);
}

void	nfork(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d (%d)\n",
			   corewar->carriages->id,
			   "fork",
			   arg_val->val[0],
			   arg_val->val[0] % IDX_MOD);
		fprintf(file, "p%5d | %s %d (%d)\n",
			   corewar->carriages->id,
			   "fork",
			   arg_val->val[0],
			   arg_val->val[0] % IDX_MOD);
	}
	push_front_carriage(head);
	(*head)->carry = corewar->carriages->carry;
	(*head)->cycle_when_live = corewar->carriages->cycle_when_live;
	ft_memcpy((*head)->reg, corewar->carriages->reg,
			sizeof(corewar->carriages->reg));
	(*head)->op_pos = do_steps(corewar->carriages->op_pos,
			arg_val->val[0] % IDX_MOD, corewar->arena);
}

void	lfork(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("p%5d | %s %d (%d)\n",
			   corewar->carriages->id,
			   "lfork",
			   arg_val->val[0],
			   arg_val->val[0]);
		fprintf(file, "p%5d | %s %d (%d)\n",
			   corewar->carriages->id,
			   "lfork",
			   arg_val->val[0],
			   arg_val->val[0]);
	}
	push_front_carriage(head);
	(*head)->carry = corewar->carriages->carry;
	(*head)->cycle_when_live = corewar->carriages->cycle_when_live;
	ft_memcpy((*head)->reg, corewar->carriages->reg,
			  sizeof(corewar->carriages->reg));
	(*head)->op_pos = do_steps(corewar->carriages->op_pos,
			arg_val->val[0], corewar->arena);
}
