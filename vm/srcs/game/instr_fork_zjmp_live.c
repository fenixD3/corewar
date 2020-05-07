#include "vm.h"

void    live(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	t_champion	*champ;

	if (!*head)
	    return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d\n",
			   corewar->carriages->id, "live", arg_val->val[0]);
		fprintf(file, "P%5d | %s %d\n",
			   corewar->carriages->id, "live", arg_val->val[0]);
	}
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

void	zjump(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d ",
			   corewar->carriages->id,
			   "zjmp",
			   (int16_t)arg_val->val[0]);
		fprintf(file, "P%5d | %s %d ",
			   corewar->carriages->id,
			   "zjmp",
				(int16_t)arg_val->val[0]);
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
		(int16_t)arg_val->val[0] % IDX_MOD, corewar->arena);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("OK\n");
		fprintf(file, "OK\n");
	}
}

void	nfork(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	push_front_carriage(head);
	(*head)->carry = corewar->carriages->carry;
	(*head)->cycle_when_live = corewar->carriages->cycle_when_live;
	ft_memcpy((*head)->reg, corewar->carriages->reg,
			sizeof(corewar->carriages->reg));
	(*head)->op_pos = do_steps(corewar->carriages->op_pos,
		(int16_t)arg_val->val[0] % IDX_MOD, corewar->arena);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d (%ld)\n",
			   corewar->carriages->id,
			   "fork",
			   (int16_t)arg_val->val[0],
			   ((int16_t)arg_val->val[0] < 0 && corewar->carriages->op_pos + (int16_t)arg_val->val[0] % IDX_MOD < corewar->arena)
			   	? (*head)->op_pos - corewar->arena - MEM_SIZE
			   	: (*head)->op_pos - corewar->arena);
		fprintf(file, "P%5d | %s %d (%ld)\n",
				corewar->carriages->id,
				"fork",
				(int16_t)arg_val->val[0],
				((int16_t)arg_val->val[0] < 0 && corewar->carriages->op_pos + (int16_t)arg_val->val[0] % IDX_MOD < corewar->arena)
				? (*head)->op_pos - corewar->arena - MEM_SIZE
				: (*head)->op_pos - corewar->arena);
	}
}

void	lfork(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d (%ld)\n",
			   corewar->carriages->id,
			   "lfork",
			   (int16_t)arg_val->val[0],
			   ((int16_t)arg_val->val[0] < 0 && corewar->carriages->op_pos + (int16_t)arg_val->val[0] % IDX_MOD < corewar->arena)
			   ? (*head)->op_pos - corewar->arena - MEM_SIZE
			   : (*head)->op_pos - corewar->arena);
		fprintf(file, "P%5d | %s %d (%ld)\n",
			   corewar->carriages->id,
			   "lfork",
				(int16_t)arg_val->val[0],
				((int16_t)arg_val->val[0] < 0 && corewar->carriages->op_pos + (int16_t)arg_val->val[0] % IDX_MOD < corewar->arena)
				? (*head)->op_pos - corewar->arena - MEM_SIZE
				: (*head)->op_pos - corewar->arena);
	}
	push_front_carriage(head);
	(*head)->carry = corewar->carriages->carry;
	(*head)->cycle_when_live = corewar->carriages->cycle_when_live;
	ft_memcpy((*head)->reg, corewar->carriages->reg,
			  sizeof(corewar->carriages->reg));
	(*head)->op_pos = do_steps(corewar->carriages->op_pos,
		(int16_t)arg_val->val[0], corewar->arena);
}
