/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:11:02 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 18:47:22 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_info *info, t_command *cmd)
{
	t_env	*env;

	env = info->env;
	if (cmd->argc > 1)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		exit(127);
	}
	while (env)
	{
		if (env->value != 0)
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	exit(0);
}
