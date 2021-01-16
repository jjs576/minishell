/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:09:59 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/15 20:11:28 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(t_env *env)
{
	while (env)
	{
		if (env->value == NULL)
			ft_printf("declare -x %s \n", env->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}

	return //뭐로 해놧니?
}

void		ft_export(t_info *info, t_command *cmd)
{
	char	**str;
	int		i;

	i = 0;
	ft_bzero(buf, MAX_PATH_LENGTH);
	if (cmd->argc == 1)
		return (print_export(info->env));
	else
	{
		//valid key값 해줘야된
		while (++i < cmd->argc)
		{
			str = ft_split(argv[1], '=');
			env_update(&info->env, str[0], str[1]);
			free_2d(str); 
		}
	}
	//return 이랑 직전의 리턴값 넣는애에 넣어주기
}
