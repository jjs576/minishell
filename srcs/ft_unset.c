/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:10:44 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 14:52:35 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isdigit(key[i]))
		return (0);
	while (key[i])
	{
		if (ft_strchr("\\\'\"$&|; @!`=", key[i]))
			return (0);
		i++;
	}
	return (1);
}

void		ft_unset(t_info *info, t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		if (!is_valid_key(cmd->argv[i]))
		{
			info->returned = 1;
			ft_putstr_fd("sh: unset: `", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue;
		}
		env_delete(&info->env, cmd->argv[i]);
	}
	info->returned = 0;
}
