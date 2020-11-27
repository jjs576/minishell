/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:40:54 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/27 18:47:33 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_info *info, char *envp[])
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
				break;
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
