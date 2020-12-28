/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:18:01 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/28 16:05:27 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void token_to_command(t_info *info)
{
	t_token *cur_token;

	cur_token = info->token;
	info->cmd = cmd_new();
	while (cur_token)
	{
		if (!ft_strcmp(cur_token->str, "|"))
		{
			cmd_push_back(&info->cmd);
			cmd_last(info->cmd)->flag |= CMD_PIPE;
		}
		else if (!ft_strcmp(cur_token->str, ";"))
		{
			cmd_push_back(&info->cmd);
			cmd_last(info->cmd)->flag |= CMD_SEMIC;
		}
		else
		{
			cmd_update(cmd_last(info->cmd), cur_token->str);
		}
		cur_token = cur_token->next;
	}
}
