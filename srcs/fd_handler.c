/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 22:29:37 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 17:20:54 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir(t_command *cmd, t_command *rdir)
{
	if (rdir->flag == CMD_INPUT)
	{
		close_fd(cmd->fd_in);
		cmd->fd_in = open(rdir->argv[0], O_RDONLY | O_CREAT, 0644);
	}
	else if (rdir->flag == CMD_TRUNC)
	{
		close_fd(cmd->fd_out);
		cmd->fd_out = open(rdir->argv[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (rdir->flag == CMD_APPEND)
	{
		close_fd(cmd->fd_out);
		cmd->fd_out = open(rdir->argv[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

void		handle_fd(t_info *info)
{
	t_command	*cmd;
	t_command	*redir;
	int			i;

	i = 0;
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
