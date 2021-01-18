/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_replacer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:21:19 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/18 12:20:47 by jjoo             ###   ########.fr       */
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
		if (ft_strchr("\\\'\"$&|; @!`?=", str[size]))
			break ;
	sliced = ft_substr(str, 0, size);
	ret = env_search(&info->env, sliced);
	if (!ret)
		ret = env_new(sliced, "");
	free(sliced);
	return (ret);
}

static char		*replace_ev(t_info *info, char *ev, int *i)
{
	char	*ret;
	t_env	*found;

	if (!ft_strcmp(ev, "?"))
	{
		ret = ft_itoa(info->returned);
		*i += ft_strlen(ret);
		return (ret);
	}
	else
	{
		found = find_env(info, ev);
		*i += ft_strlen(found->key);
		return (ft_strdup(found->value));
	}
}

void			replace_input(t_info *info)
{
	char	ret[MAX_STR];
	int		i;
	char	*temp;
	int		flag;

	flag = 0;
	i = -1;
	ret[0] = 0;
	while (info->input[++i])
	{
		if (info->input[i] == '\'' && !(flag & TK_DQOUTE))
			flag ^= TK_QOUTE;
		if (info->input[i] == '\"' && !(flag & TK_QOUTE))
			flag ^= TK_DQOUTE;
		if (!(flag & TK_QOUTE) && info->input[i] == '$')
			temp = replace_ev(info, &info->input[i + 1], &i);
		else
			temp = ft_substr(info->input, i, 1);
		ft_strlcat(ret, temp, MAX_STR);
		free(temp);
	}
	ft_bzero(info->input, info->input_len);
	ft_strlcat(info->input, ret, MAX_STR);
}
