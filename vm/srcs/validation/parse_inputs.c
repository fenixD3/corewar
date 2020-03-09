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
			if (corewar->flgs.flgs & N_FLG)
			{
				if (is_champion(av[++i], corewar))
					get_error("After -n flag must be a number");
				if ((corewar->flgs.nxt_player_num = ft_atoi(av[i])) <= 0 ||
				corewar->flgs.nxt_player_num > MAX_PLAYERS)
					get_error(ERR_NUM_AFT_N_FLG);
				if (!is_champion(av[++i], corewar))
					get_error("After -n <num> must be a champion");
				corewar->flgs.flgs ^= N_FLG;
			}
			else if (corewar->flgs.flgs & DUMP_FLG)
				corewar->flgs.nbr_cycles_dump = ft_atoi(av[++i]);
		}
		else if (!is_champion(av[i], corewar))
			get_error("Champion file should contain .cor completion");
	}
	validation_champions(corewar->champs);
}

void	validation_champions(t_champion *champs)
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
		champs = champs->next;
	}
}

void	byte_code_validation(const int fd, t_champion *champ)
{
	ssize_t	rd_cnt;

	rd_cnt = read(fd, &champ->file.header.magic, 4);
	reverse_bytes(&champ->file.header.magic);
	if (rd_cnt < 4 || champ->file.header.magic != COREWAR_EXEC_MAGIC)
		get_error("There isn't magic or magic is incorrect");
	rd_cnt = read(fd, champ->file.header.prog_name, PROG_NAME_LENGTH);
	champ->file.header.prog_name[rd_cnt] = '\0';
	rd_cnt = read(fd, &champ->file.zero, 4);
	if (champ->file.zero)
		get_error("There isn't 4 NULL bytes after champion's name or \
champion's name is too big");
	rd_cnt = read(fd, &champ->file.header.prog_size, 4);
	reverse_bytes(&champ->file.header.prog_size);
	if (champ->file.header.prog_size > CHAMP_MAX_SIZE)
		get_error("Champion's code size is too big");
	rd_cnt = read(fd, champ->file.header.comment, COMMENT_LENGTH);
	champ->file.header.comment[rd_cnt] = '\0';
	rd_cnt = read(fd, &champ->file.zero, 4);
	if (champ->file.zero)
		get_error("There isn't 4 NULL bytes after champion's comment or \
champion's comment is too big");
	rd_cnt = read(fd, champ->file.exec_code, CHAMP_MAX_SIZE);
}
