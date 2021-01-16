/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:40:54 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 18:48:15 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_env(t_info *info, char *envp[])
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				key = ft_substr(envp[i], 0, j);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
				break ;
			}
			j++;
		}
		env_push_back(&(info->env), key, value);
		if (!ft_strcmp(key, "PWD"))
			ft_strlcat(info->pwd, value, MAX_PATH_LENGTH);
		free(key);
		free(value);
	}
}

static int	get_env_len(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->value)
			n += 1;
		env = env->next;
	}
	return (n);
}

char		**get_env_array(t_info *info)
{
	int		len;
	t_env	*env;
	char	**ret;

	env = info->env;
	len = get_env_len(env);
	ret = ft_calloc(len + 1, sizeof(char*));
	len = 0;
	while (env)
	{
		if (env->value)
		{
			ret[len] = ft_calloc(
				ft_strlen(env->key) + ft_strlen(env->value) + 2, sizeof(char));
			ft_strlcat(ret[len], env->key, MAX_STR);
			ft_strlcat(ret[len], "=", MAX_STR);
			ft_strlcat(ret[len], env->value, MAX_STR);
		}
		env = env->next;
	}
	return (ret);
}
