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

#include "libft.h"
#include "options.h"
#include <stdint.h>
#include <stdio.h> // убрать //////////////////////////////////////////

typedef struct	s_disasm
{
    uint8_t    code;
    uint8_t    args[3];
    int        value[3];
}				t_disasm;

int		reverse_disasm_bytes(int *num_to_rev)
{
    int	rev;
    int	byte;
    int	i;

    rev = 0;
    i = 0;
    while (i < 32)
    {
        byte = *num_to_rev >> i & 0xFFu;
        rev |= byte << (32u - 8u - i);
        i += 8;
    }
    return (rev);
}

int   arguments_value(t_disasm *s, unsigned char *champ, int i, int *j)
{
    while (i < g_op[s->code - 1].num_args)
    {
        if (s->args[i] == REG_CODE && (*champ > 0 && *champ <= REG_NUMBER))
        {
            s->value[i] = *((unsigned char *)champ);
            champ++;
        }
        else if (s->args[i] == DIR_CODE && g_op[s->code - 1].size_t_dir == 4)
        {
            j = (int *)(champ);
            s->value[i] = reverse_disasm_bytes(j);
            champ += 4;
        }
        else if (s->args[i] == IND_CODE || s->args[i] == DIR_CODE)
        {
            s->value[i] = *((short *)(champ));
            s->value[i] = (((s->value[i] >> 8) & 0xFF) | ((s->value[i] << 8) & 0xFF00));
            champ += 2;
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

int     copy_string(char **str, char **string, int i)
{
    char *tmp_str;
    char *tmp_string;

    tmp_str = *str;
    tmp_string = *string;
    while (*tmp_string)
    {
        tmp_str[i++] = (*tmp_string);
        tmp_string++;
    }
    free(*string);
    *string = NULL;
    return (i);
}

int    add_dir_ind(t_disasm *s, char **str, int i, int j, unsigned char *champ)
{
    int *k;
    char *string;
    char *tmp;

    tmp = *str;
    if (s->args[j] == DIR_CODE || !(g_op[s->code - 1].argument_type_code))
        tmp[i++] = DIRECT_CHAR;
    if ((s->args[j] == DIR_CODE || !(g_op[s->code - 1].argument_type_code)) &&
    g_op[s->code - 1].size_t_dir == 4)
    {
        if (!(g_op[s->code - 1].argument_type_code))
            k = (int *)(champ);
        else
            k = &(s->value[j]);
        s->value[j] = reverse_disasm_bytes(k);
    }
    else
    {
        if (!(g_op[s->code - 1].argument_type_code))
            s->value[j] = *(short *)(champ);
        s->value[j] = (((s->value[j] >> 8) & 0xFF) | ((s->value[j] << 8) & 0xFF00));
    }
    if (!(string = ft_itoa(s->value[j])))
        return (-1);
    return (copy_string(str, &string, i));
}

int     add_reg(t_disasm *s, char **str, int i, int j, unsigned char *champ)
{
    char *string;
    char *tmp;

    tmp = *str;
    if (s->args[j] == REG_CODE)
    {
        tmp[i++] = REGISTER_CHAR;
        if (!(string = ft_itoa(s->value[j])))
            return (-1);
        return (copy_string(str, &string, i));
    }
    return (add_dir_ind(s, str, i, j, champ));
}

char    *command_output(t_disasm *s, unsigned char *champ, int i, int j)
{
    char    *str;

    str = ft_strnew(100);
    while (g_op[s->code - 1].name[i])
    {
        str[i] = g_op[s->code - 1].name[i];
        i++;
    }
    str[i++] = ' ';
    if (!(g_op[s->code - 1].argument_type_code))
        add_dir_ind(s, &str, i, j, champ);
    while (j < g_op[s->code - 1].num_args && g_op[s->code - 1].argument_type_code)
    {
        i = add_reg(s, &str, i, j, champ);
        if (i < 0)
            return (NULL);
        if (++j < g_op[s->code - 1].num_args)
        {
            str[i++] = SEPARATOR_CHAR;
            str[i++] = ' ';
        }
    }
    return (str);
}

char *disasm_error(char *string)
{
    char *str;

    if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1))))
        return (NULL);
    ft_strcpy(str, string);
    return (str);
}

char    *disasm(unsigned char *champ)
{
    int     i;
    int     j;
    int     *k;
    t_disasm s;

    i = 0;
    j = 0;
    k = NULL;
    if (!(*champ > 0 && *champ < 17))
        return (disasm_error("Incorrect command"));
    s.code = *champ;
    s.args[0] = '0';
    champ++;
    if (!(g_op[s.code - 1].argument_type_code))
        return(command_output(&s, champ, i, j));
    else if (!types_of_args(*champ, &s))
        return (disasm_error("Incorrect command arguments"));
    if (!arguments_value(&s, ++champ, i, k))
        return (disasm_error("Incorrect value of T_REG"));
    return (command_output(&s, champ, i, j));
}

//int main(void)
//{
//    unsigned char *s = "\at\a\t\r\aA\t";
//    printf("%s", disasm(s));
//    return (0);
//}