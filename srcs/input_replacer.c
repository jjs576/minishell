/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_replacer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:21:19 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/30 22:35:30 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_env(t_info *info, char *str)
{
	int		size;
	char	*sliced;
	t_env	*ret;

	size = -1;
	while (str[++size])
		if (ft_strchr(" \'\"|;",str[size]))
			break ;
	sliced = ft_substr(str, 0, size);
	ret = env_search(&info->env, sliced);
	if (!ret)
		ret = env_new(sliced, "");
	free(sliced);
	return (ret);
}

void		replace_input(t_info *info)
{
	char	ret[MAX_STR];
	int		i;
	t_env	*found_env;

	i = -1;
	ret[0] = 0;
	while (info->input[++i])
		if (info->input[i] == '$' && info->input[i + 1] && info->input[i + 1] != ' ')
		{
			if (info->input[i + 1] == '?')
			{
				i += 1;
				ft_strlcat(ret, ft_itoa(info->returned), MAX_STR);
			}
			else
			{
				found_env = find_env(info, &info->input[i + 1]);
				i += ft_strlen(found_env->key);
				ft_strlcat(ret, found_env->value, MAX_STR);
			}
		}
		else
			ft_strlcat(ret, ft_substr(info->input, i, 1), MAX_STR);
	ft_bzero(info->input, info->input_len);
	ft_strlcat(info->input, ret, MAX_STR);
}
