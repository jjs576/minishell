/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:09:59 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 17:14:10 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(t_env *env)
{
	while (env)
	{
		if (env->value == NULL)
			ft_printf("declare -x %s\n", env->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

static int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isdigit(key[i]))
		return (0);
	while (key[i])
	{
		if (ft_strchr("\\\'\"$&|; @!`", key[i]))
			return (0);
		i++;
	}
	return (1);
}

void		ft_export(t_info *info, t_command *cmd)
{
	char	**str;
	int		i;

	i = 0;
	if (cmd->argc == 1)
	{
		info->returned = 0;
		print_export(info->env);
	}
	else
	{
		while (++i < cmd->argc)
		{
			str = ft_split(cmd->argv[1], '=');
			if (!is_valid_key(str[0]))
			{
				info->returned = 1;
				free_2d(str);
				continue ;
			}
			env_update(&info->env, str[0], str[1]);
			free_2d(str);
			info->returned = 0;
		}
	}
}
