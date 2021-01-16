/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_replacer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:21:19 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 22:41:28 by jjoo             ###   ########.fr       */
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
	char	*temp;

	i = -1;
	ret[0] = 0;
	while (in->input[++i])
		if (in->input[i] == '$' && in->input[i + 1] && in->input[i + 1] != ' ')
		{
			if (in->input[i + 1] == '?')
				i += (ft_strlcat(ret, ft_itoa(in->returned), MAX_STR)) % 1 | 1;
			else
			{
				ft_strlcat(ret, find_env(in, &in->input[i + 1])->value, 1000);
				i += ft_strlen(find_env(in, &in->input[i + 1])->key);
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
