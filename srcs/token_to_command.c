/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:18:01 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 22:28:54 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_command_flag(t_token *token)
{
	if (!ft_strcmp(token->str, "|"))
		return (CMD_PIPE);
	else if (!ft_strcmp(token->str, ";"))
		return (CMD_END);
	else if (!ft_strcmp(token->str, ";;"))
		return (CMD_ERROR);
	else if (token->flag & TK_REDIR)
	{
		if (!ft_strcmp(token->str, "<"))
			return (CMD_INPUT);
		else if (!ft_strcmp(token->str, ">"))
			return (CMD_TRUNC);
		else if (!ft_strcmp(token->str, ">>"))
			return (CMD_APPEND);
		return (CMD_ERROR);
	}
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
		flag = 0;
		if (cur_token->flag & (TK_PIPE | TK_END | TK_REDIR))
			if ((flag = get_command_flag(cur_token)) & CMD_ERROR)
			{
				ft_putendl_fd("sh: syntax error near unexpected token", 2);
				info->returned = 258;
				info->status |= INFO_DONT_EXEC;
			}
		if (flag && !(flag & CMD_ERROR) && flag & CMD_END)
			cmd_last(info->cmd)->flag |= flag;
		if (flag && !(flag & CMD_ERROR))
			cmd_push_back(&info->cmd);
		if (flag && !(flag & CMD_ERROR) && !(flag & CMD_END))
			cmd_last(info->cmd)->flag |= flag;
		if (!(flag && !(flag & CMD_ERROR)))
			cmd_update(cmd_last(info->cmd), cur_token->str);
		cur_token = cur_token->next;
	}
}
