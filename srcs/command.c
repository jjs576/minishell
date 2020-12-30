/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:31:19 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/30 22:11:24 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*cmd_new()
{
	t_command	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_command));
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
