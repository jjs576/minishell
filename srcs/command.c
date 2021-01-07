/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:31:19 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/07 20:21:36 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*cmd_new()
{
	t_command	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_command));
	new_cmd->fd_in = -1;
	new_cmd->fd_out = -1;
	return (new_cmd);
}

void			cmd_update(t_command *cmd, char *str)
{
	ft_strlcpy(cmd->argv[cmd->argc], str, MAX_STR);
	cmd->argc++;
}

t_command		*cmd_last(t_command *head)
{
	if (!head)
		return (0);
	while (head->next)
		head = head->next;
	return (head);
}
void			cmd_push_back(t_command **head)
{
	t_command		*cmd;

	if (!*head)
		*head = cmd_new();
	else
	{
		cmd = *head;
		while (cmd->next)
			cmd = cmd->next;
		cmd->next = cmd_new();
	}
}

void			cmd_delete_redir(t_command **head)
{
	t_command	*cmd;
	t_command	*erase;

	cmd = *head;
	if (cmd->flag & (CMD_APPEND | CMD_INPUT | CMD_TRUNC))
	{
		*head = (*head)->next;
		free(cmd);
		return ;
	}
	while (cmd->next)
	{
		if (cmd->next && cmd->next->flag & (CMD_APPEND | CMD_INPUT | CMD_TRUNC))
		{
			erase = cmd->next;
			cmd->next = cmd->next->next;
			free(erase);
			return ;
		}
		cmd = cmd->next;
	}
}
