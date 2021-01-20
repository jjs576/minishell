/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:35:28 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/20 17:29:38 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '-')
		return (0);
	while (s[++i])
		if (s[i] != 'n')
			return (0);
	return (1);
}

void		ft_echo(t_command *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd->argv[i] && !ft_strncmp(cmd->argv[i], "-", 1))
	{
		if (!(flag |= check_flag(cmd->argv[i])))
			break ;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!flag)
		ft_printf("\n");
	exit(0);
}
