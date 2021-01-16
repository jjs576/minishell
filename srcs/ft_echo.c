/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:35:28 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 18:22:12 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_info *info, t_command *cmd)
{
	int	i;
	int	flag;

	flag = 1;
	i = 1;
	if (cmd->argc > 2)
	{
		while (cmd->argv[i] && (ft_strcmp(cmd->argv[i], "-n") == 0))
		{
			flag = 0;
			i++;
		}
	}
	while (cmd->argv[i])
	{
		ft_printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (flag)
		ft_printf("\n");
	info->returned = 0;
	exit(0);
}
