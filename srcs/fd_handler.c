/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 22:29:37 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/05 21:29:30 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipe(t_command *cmd, t_command *redir)
{

}

static void	handle_redir(t_command *cmd, t_command *redir)
{

}

static void	handle_std(t_command *cmd)
{

}

void		handle_fd(t_info *info)
{
	t_command	*cmd;
	t_command	*redir;

	cmd = info->cmd;
	while (cmd)
	{
		redir = 0;
		if (cmd->next &&
		cmd->next->flag & (CMD_APPEND | CMD_INPUT | CMD_TRUNC | CMD_PIPE))
			redir = cmd->next;
		if (redir)
			handle_pipe(cmd, redir);
		else if (redir->flag & (CMD_APPEND | CMD_INPUT | CMD_TRUNC))
			handle_redir(cmd, redir);
		else
			handle_std(cmd);

		if (redir && !(redir->flag & CMD_PIPE))
			cmd = redir->next;
		else
			cmd = cmd->next;
	}
}

