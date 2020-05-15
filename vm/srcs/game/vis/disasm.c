/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <hecvi@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 21:28:48 by klaurine          #+#    #+#             */
/*   Updated: 2020/04/28 21:30:51 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "options.h"
#include <stdint.h>

typedef struct	s_disasm
{
	uint8_t    code;
	uint8_t    args[3];
	int        value[3];
	unsigned char *arena;
	unsigned char *bogie;
}				t_disasm;


size_t	len_num(int num)
{
	if (num >= 0 && num <= 9)
		return (1);
	return (len_num(num / 10) + 1);
}

int     from_int_to_char(int n, char **s, int i)
{
	int             j;
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

int   arguments_value(t_disasm *s, unsigned char *champ, int i)
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
			s->value[i] = (((s->value[i] >> 8) & 0xFF) | ((s->value[i] << 8) & 0xFF00));
			champ = do_steps(champ, 2, s->arena);
		}
		else
			return (0);
		i++;
	}
	return (1);
}

int    types_of_args(unsigned char type, t_disasm *s)
{
	int     i;
	int     j;
	char    tmp;

	i = 0;
	j = 6;
	while (i < g_op[s->code - 1].num_args)
	{
		tmp = (type >> j) & 3;
		if (tmp == REG_CODE && !(T_REG & g_op[s->code - 1].args_type[i]))
			return (0);
		else if (tmp == IND_CODE && !(T_IND & g_op[s->code - 1].args_type[i]))
			return (0);
		else if (tmp == DIR_CODE && !(T_DIR & g_op[s->code - 1].args_type[i]))
			return (0);
		else if (!tmp)
			return (0);
		s->args[i] = tmp;
		i++;
		j -= 2;
	}
	return (1);
}

int    add_dir_ind(t_disasm *s, char **str, int i, int j, unsigned char *champ)
{
	char *tmp;

	tmp = *str;
	if (s->args[j] == DIR_CODE || !(g_op[s->code - 1].argument_type_code))
		tmp[i++] = DIRECT_CHAR;
	if (!(g_op[s->code - 1].argument_type_code) && g_op[s->code - 1].size_t_dir == 4)
		s->value[j] = reverse_vm_bytes(champ, 4, s->arena);
	else if (!(g_op[s->code - 1].argument_type_code))
	{
		s->value[j] = *(short *)(champ);
		s->value[j] = (((s->value[j] >> 8) & 0xFF) | ((s->value[j] << 8) & 0xFF00));
	}
	return (from_int_to_char(s->value[j], str, i));
}

int     add_reg(t_disasm *s, char **str, int i, int j, unsigned char *champ)
{
	char *tmp;

	tmp = *str;
	if (s->args[j] == REG_CODE)
	{
		tmp[i++] = REGISTER_CHAR;
		return (from_int_to_char(s->value[j], str, i));
	}
	return (add_dir_ind(s, str, i, j, champ));
}

void    command_output(t_disasm *s, unsigned char *champ, int i, int j, char **str)
{
	char    *tmp;

	tmp = *str;
	while (g_op[s->code - 1].name[i])
	{
		tmp[i] = g_op[s->code - 1].name[i];
		i++;
	}
	tmp[i++] = ' ';
	if (!(g_op[s->code - 1].argument_type_code))
	{
		i = add_dir_ind(s, str, i, j, champ);
		tmp[i] = '\0';
	}
	while (j < g_op[s->code - 1].num_args && g_op[s->code - 1].argument_type_code)
	{
		i = add_reg(s, str, i, j, champ);
		if (++j < g_op[s->code - 1].num_args)
		{
			tmp[i++] = SEPARATOR_CHAR;
			tmp[i++] = ' ';
		}
		tmp[i] = '\0';
	}
}

void    disasm_error(char *str_error, char **str)
{
	int		c;

	c = 0;
	ft_sprintf(*str, "%s\n", str_error);
	while ((*str)[c] != '\n')
		c++;
	(*str)[c] = '\0';
}

void    disasm(t_carriages *champ, char *str, unsigned char *arena)
{
	int     i;
	int     j;
	t_disasm s;

	i = 0;
	j = 0;
	ft_bzero(str, 35);
	if (champ->cycle_op < 0 || champ->op_code == 0 || champ->op_code > 16)
		return (disasm_error("Incorrect command", &str));
	s.code = champ->op_code;
	s.args[0] = '0';
	s.arena = arena;
	s.bogie = do_steps(champ->op_pos, 1, arena);
	if (!(g_op[s.code - 1].argument_type_code))
		return(command_output(&s, s.bogie, i, j, &str));
	else if (!types_of_args(*(s.bogie), &s))
		return (disasm_error("Incorrect command arguments", &str));
	if (!arguments_value(&s, do_steps(s.bogie, 1, arena), i))
		return (disasm_error("Incorrect value of T_REG", &str));
	return (command_output(&s, s.bogie, i, j, &str));
}
