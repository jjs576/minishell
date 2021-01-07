/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 22:29:37 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/07 20:37:16 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir(t_command *cmd, t_command *redir)
{

	if (redir->flag == CMD_INPUT)
	{
		fd_close(cmd->fd_in);
		cmd->fd_in = open(redir->argv[0], O_RDONLY);
	}
	else if (redir->flag == CMD_TRUNC)
	{
		fd_close(cmd->fd_out);
		cmd->fd_out = open(redir->argv[0], O_CREAT | O_WRONLY | O_TRUNC);
	}
	else if (redir->flag == CMD_APPEND)
	{
		fd_close(cmd->fd_out);
		cmd->fd_out = open(redir->argv[0], O_CREAT | O_WRONLY | O_APPEND);
	}
}

void		handle_fd(t_info *info)
{
	t_command	*cmd;
	t_command	*redir;
	int			i;

	cmd = info->cmd;
	while (cmd)
	{
		redir = 0;
		if (cmd->next &&
		cmd->next->flag & (CMD_APPEND | CMD_INPUT | CMD_TRUNC))
		{
			redir = cmd->next;
			i++;
		}
		if (redir && redir->flag & (CMD_APPEND | CMD_INPUT | CMD_TRUNC))
			handle_redir(cmd, redir);
		if (redir && !(redir->flag & CMD_PIPE))
			cmd = redir->next;
		else
			cmd = cmd->next;
	}
	while (i--)
		cmd_delete_redir(&info->cmd);
	cmd_last(info->cmd)->flag |= CMD_END;
}
