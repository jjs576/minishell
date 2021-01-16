/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:10:44 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/17 00:17:14 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_argument(char *s)
{
	int		num;
	char	*num_itoa;
	int		ret;

	num = ft_atoi(s);
	num_itoa = ft_itoa(num);
	ret = strcmp(s, num_itoa);
	free(num_itoa);
	return (!ret);
}

void		ft_exit(t_info *info, t_command *cmd)
{
	ft_printf("exit\n", 2);
	info->status |= INFO_EXIT;
	if (cmd->argc == 1)
	{
		info->exit_return = 0;
	}
	else if (cmd->argc == 2)
		if (is_numeric_argument(cmd->argv[1]))
			info->exit_return = ft_atoi(cmd->argv[1]);
		else
		{
			ft_putendl_fd("sh: exit: numeric argument required", 2);
			info->returned = 255;
		}
	else
	{
		ft_putendl_fd("sh: exit: too many arguments", 2);
		info->exit_return = 2;
	}
}
