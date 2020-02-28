//
// Created by Mort Deanne on 28/02/2020.
//

int		ft_wordequ(char *ethalon, char *str, char *delims)
{
	while (*ethalon && *str)
	{
		if (!*ethalon && *str)
		{
			while (*delims)
			{
				if (*str == *delims)
					return (1);
				delims++;
			}
			return (0);
		}
		if (*ethalon != *str)
			return (0);
		ethalon++;
		str++;
	}
	return (1);
}
