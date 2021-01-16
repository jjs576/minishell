/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_replacer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:21:19 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 21:30:19 by jjoo             ###   ########.fr       */
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
		if (ft_strchr(" \'\"|;", str[size]))
			break ;
	sliced = ft_substr(str, 0, size);
	ret = env_search(&info->env, sliced);
	if (!ret)
		ret = env_new(sliced, "");
	free(sliced);
	return (ret);
}

void			replace_input(t_info *in)
{
	char	ret[MAX_STR];
	int		i;
	t_env	*found_env;
	char	*temp;

	i = -1;
	ret[0] = 0;
	while (in->input[++i])
		if (in->input[i] == '$' && in->input[i + 1] && in->input[i + 1] != ' ')
		{
			if (in->input[i + 1] == '?')
			{
				i += 1;
				ft_strlcat(ret, ft_itoa(in->returned), MAX_STR);
			}
			else
			{
				found_env = find_env(in, &in->input[i + 1]);
				i += ft_strlen(found_env->key);
				ft_strlcat(ret, found_env->value, MAX_STR);
			}
		}
		else
		{
			temp = ft_substr(in->input, i, 1);
			ft_strlcat(ret, temp, MAX_STR);
			free(temp);
		}
	ft_bzero(in->input, in->input_len);
	ft_strlcat(in->input, ret, MAX_STR);
}
