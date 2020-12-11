/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:05:31 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/11 22:01:06 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(t_info *info)
{
	int		i;
	int		cur_quote;

	i = -1;
	cur_quote = 0;
	info->token = token_new("");
	while (info->input[++i])
	{
		if (info->input)
		{

		}
	}
}
