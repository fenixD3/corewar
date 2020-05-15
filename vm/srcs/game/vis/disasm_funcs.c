
#include "disasm.h"

size_t	len_num(int num)
{
	if (num >= 0 && num <= 9)
		return (1);
	return (len_num(num / 10) + 1);
}

int		from_int_to_char(int n, char **s, int i)
{
	int				j;
	char			*str;
	size_t			len;
	unsigned int	nbr;

	j = len_num(n);
	len = j;
	str = *s;
	nbr = (n < 0) ? (unsigned int)(-n) : (unsigned int)(n);
	if (nbr == 0)
		str[i] = '0';
	while (len-- && nbr)
	{
		str[i + len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
	{
		str[i + len] = '-';
		j++;
	}
	return (i + j);
}

int		arguments_value(t_disasm *s, unsigned char *champ, int i)
{
	while (i < g_op[s->code - 1].num_args)
	{
		if (s->args[i] == REG_CODE && (*champ > 0 && *champ <= REG_NUMBER))
		{
			s->value[i] = *((unsigned char *)champ);
			champ = do_steps(champ, 1, s->arena);
		}
		else if (s->args[i] == DIR_CODE && g_op[s->code - 1].size_t_dir == 4)
		{
			s->value[i] = reverse_vm_bytes(champ, 4, s->arena);
			champ = do_steps(champ, 4, s->arena);
		}
		else if (s->args[i] == IND_CODE || s->args[i] == DIR_CODE)
		{
			s->value[i] = *((short *)(champ));
			s->value[i] = (((s->value[i] >> 8) & 0xFF) |
												((s->value[i] << 8) & 0xFF00));
			champ = do_steps(champ, 2, s->arena);
		}
		else
			return (0);
		i++;
	}
	return (1);
}

int		add_dir_ind(t_disasm *s, char **str, int i, int j)
{
	char *tmp;

	tmp = *str;
	if (s->args[j] == DIR_CODE || !(g_op[s->code - 1].argument_type_code))
		tmp[i++] = DIRECT_CHAR;
	if (!(g_op[s->code - 1].argument_type_code) &&
		g_op[s->code - 1].size_t_dir == 4)
		s->value[j] = reverse_vm_bytes(s->bogie, 4, s->arena);
	else if (!(g_op[s->code - 1].argument_type_code))
	{
		s->value[j] = *(short *)(s->bogie);
		s->value[j] = (((s->value[j] >> 8) & 0xFF) |
												((s->value[j] << 8) & 0xFF00));
	}
	return (from_int_to_char(s->value[j], str, i));
}

int		add_reg(t_disasm *s, char **str, int i, int j)
{
	char *tmp;

	tmp = *str;
	if (s->args[j] == REG_CODE)
	{
		tmp[i++] = REGISTER_CHAR;
		return (from_int_to_char(s->value[j], str, i));
	}
	return (add_dir_ind(s, str, i, j));
}
