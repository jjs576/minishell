/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:20:57 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/14 00:05:43 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_fd(t_command *cmd, int fd[MAX_COMMAND][2], int index)
{
	if (index > 0)
		dup2(fd[index - 1][0], STDIN);
	if (!(cmd->flag & CMD_END))
		dup2(fd[index][1], STDOUT);
	if (cmd->fd_out != -1)
		dup2(cmd->fd_out, STDOUT);
	if (cmd->fd_in != -1)
		dup2(cmd->fd_in, STDIN);
}

void	wait_forked(t_info *info)
{
	t_command	*cmd;
	int			status;

	cmd = info->cmd;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFSIGNALED(status))
			info->returned = WTERMSIG(status) + 128;
		else if (WIFSTOPPED(status))
			info->returned = WSTOPSIG(status);
		else
			info->returned = WEXITSTATUS(status);
		cmd = cmd->next;
	}
}
