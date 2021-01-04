/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:18:01 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/05 00:11:44 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_command_flag(t_token *token)
{
	if (!ft_strcmp(token->str, "|"))
		return (CMD_PIPE);
	else if (!ft_strcmp(token->str, ";"))
		return (CMD_END);
	else if (!ft_strcmp(token->str, "<"))
		return (CMD_INPUT);
	else if (!ft_strcmp(token->str, ">"))
		return (CMD_INPUT);
	else if (!ft_strcmp(token->str, ">>"))
		return (CMD_APPEND);
	return (0);
}

void		token_to_command(t_info *info)
{
	t_token	*cur_token;
	int		flag;

	cur_token = info->token;
	info->cmd = cmd_new();
	while (cur_token)
	{
		flag = get_command_flag(cur_token);
		cmd_last(info->cmd)->flag |= flag;
		if (cmd_last(info->cmd)->flag & (CMD_PIPE | CMD_END))
			cmd_push_back(&info->cmd);
		else
			cmd_update(cmd_last(info->cmd), cur_token->str);
		cur_token = cur_token->next;
	}
}
