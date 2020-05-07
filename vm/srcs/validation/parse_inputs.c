#include "vm.h"
#include "error_defs.h"

void	parse_arguments(int ac, char **av, t_corewar *corewar)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (is_flg(av[i], &corewar->flgs))
		{
			if (corewar->flgs.set_flg & N_FLG)
			{
				if (is_champion(av[++i], corewar))
					get_error("After -n flag must be a number");
				if ((corewar->flgs.nxt_player_num = ft_atoi(av[i])) <= 0 ||
				corewar->flgs.nxt_player_num > MAX_PLAYERS)
					get_error(ERR_NUM_AFT_N_FLG);
				if (!is_champion(av[++i], corewar))
					get_error("After -n <num> must be a champion");
				corewar->flgs.set_flg ^= N_FLG;
			}
			else if (corewar->flgs.set_flg & DUMP_FLG)
			{
				if (is_champion(av[++i], corewar))
					get_error("After -dump flag must be a number");
				corewar->flgs.nbr_cycles_dump = ft_atoi(av[i]);
			}
			else if (corewar->flgs.set_flg & V_FLG) /// not need in final!
				corewar->flgs.verb_num = ft_atoi(av[++i]);
		}
		else if (!is_champion(av[i], corewar))
			get_error("Champion file should contain .cor completion");
	}
	validation_champions(corewar->champs, &corewar->game_param);
}

void	validation_champions(t_champion *champs, t_game_param *game_params)
{
	int		fd;
	int		cur_champ_num;

	if (champions_cnt(champs) > MAX_PLAYERS)
		get_error("So much champions count");
	if (max_champs_num(champs) > champions_cnt(champs))
		get_error("The number after one of champion is more than count of \
champions in this battle");
	cur_champ_num = 1;
	while (champs)
	{
		if ((fd = open(champs->filename, O_RDONLY)) <= 0)
			get_error("Couldn't open file or this was a directory");
		byte_code_validation(fd, champs);
		while (!champs->num && is_there_same_champ_num(champs, cur_champ_num))
			++cur_champ_num;
		if (!champs->num)
			champs->num = cur_champ_num++;
		if (!champs->next)
			game_params->who_lst_live = champs->num;
		champs = champs->next;
	}
}

void	byte_code_validation(const int fd, t_champion *champ)
{
	ssize_t	rd_cnt;

	rd_cnt = read(fd, &champ->file.header.magic, 4);
	reverse_int_bytes(&champ->file.header.magic);
	if (rd_cnt < 4 || champ->file.header.magic != COREWAR_EXEC_MAGIC)
		get_error("There isn't magic or magic is incorrect");
	rd_cnt = read(fd, champ->file.header.prog_name, PROG_NAME_LENGTH);
	champ->file.header.prog_name[rd_cnt] = '\0';
	rd_cnt = read(fd, &champ->file.zero, 4);
	if (champ->file.zero)
		get_error(ERR_NOT_NULL);
	rd_cnt = read(fd, &champ->file.header.prog_size, 4);
	reverse_int_bytes(&champ->file.header.prog_size);
	if (champ->file.header.prog_size > CHAMP_MAX_SIZE
			|| !champ->file.header.prog_size)
		get_error("Champion's code size is too big or equal 0");
	rd_cnt = read(fd, champ->file.header.comment, COMMENT_LENGTH);
	champ->file.header.comment[rd_cnt] = '\0';
	rd_cnt = read(fd, &champ->file.zero, 4);
	if (champ->file.zero)
		get_error(ERR_NOT_NULL);
	rd_cnt = read(fd, champ->file.exec_code, CHAMP_MAX_SIZE);
	if (rd_cnt != champ->file.header.prog_size)
		get_error(ERR_DIFF_CODE_SIZE);
}
