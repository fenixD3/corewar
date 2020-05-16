#include "vm.h"

static void	call_printf_v_4_another(t_corewar *corewar, t_parse_args *arg_val,
									   const char *cmd)
{
	if (ft_strequ(cmd, "st"))
		print_v_4_st(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "sti"))
		print_v_4_sti(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "add"))
		print_v_4_add(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "sub"))
		print_v_4_sub(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "and"))
		print_v_4_and(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "or"))
		print_v_4_or(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "xor"))
		print_v_4_xor(corewar, arg_val, cmd);
}

void		call_printf_v_4(t_corewar *corewar, t_parse_args *arg_val,
							const char *cmd)
{
	if (ft_strequ(cmd, "live"))
		print_v_4_live(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "fork"))
		print_v_4_nfork(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "lfork"))
		print_v_4_lfork(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "zjmp"))
		print_v_4_zjmp(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "ld"))
		print_v_4_ld(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "ldi"))
		print_v_4_ldi(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "lld"))
		print_v_4_lld(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "lldi"))
		print_v_4_lldi(corewar, arg_val, cmd);
	else
		call_printf_v_4_another(corewar, arg_val, cmd);
}
