/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:35:28 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/29 23:11:21 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void ft_echo(t_info *info)
{
	int	i;
	int	flag;

	flag = 1;
	i = 1;
	if (info->cmd.argc > 2)
	{
		while (info->cmd.argv[i] && (ft_strcmp(info->cmd.argv[i], "-n") == 0))
		{
			flag = 0;
			i++;
		}
	}
	while (info->cmd.argv[i])
	{
		ft_printf("%s", info->cmd.argv[i]);
		if (info->cmd.argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (flag)
		ft_printf("\n");
	info->returned = 0;
	exit(0);
}
*/
