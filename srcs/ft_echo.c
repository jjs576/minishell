#include "minishell.h"

void ft_echo(t_state *s, t_cmd cmd)
{
	int	i;
	int	flag;

	flag = 1;
	i = 1;
	if (cmd.argv_num > 1)
	{
		while (cmd.argv[i] && (ft_strcmp(cmd.argv[i], "-n") == 0))
		{
			flag = 0;
			i++;
		}
	}
	while (cmd.argv[i])
	{
		ft_printf("%s", cmd.argv[i]);
		if (cmd.argb[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (flag)
		ft_printf("\n");
	s->ret = 0;
	exit(0);
}
