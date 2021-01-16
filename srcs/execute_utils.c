/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:20:57 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 18:21:06 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		connect_fd(t_command *cmd, int fd[MAX_COMMAND][2], int index)
{
	if (index > 0)
		dup2(fd[index - 1][0], STDIN);
	if (!(cmd->flag & CMD_END))
		dup2(fd[index][1], STDOUT);
	if (cmd->fd_out != -1)
		dup2(cmd->fd_out, STDOUT);
	if (cmd->fd_in != -1)
		dup2(cmd->fd_in, STDIN);
	return (1);
}

void	wait_forked(t_info *info)
{
	t_command	*cmd;
	int			status;

	cmd = info->cmd;
	while (cmd && cmd->argc > 0)
	{
		info->status |= INFO_WAITING;
		waitpid(cmd->pid, &status, 0);
		info->status &= ~INFO_WAITING;
		if (WIFSIGNALED(status))
			info->returned = WTERMSIG(status) + 128;
		else if (WIFSTOPPED(status))
			info->returned = WSTOPSIG(status);
		else
			info->returned = WEXITSTATUS(status);
		cmd = cmd->next;
	}
}

char	*get_correct_path(char *path, char *file)
{
	char	*buf;
	char	*bin;

	if (path[ft_strlen(path) - 1] != '/')
		buf = ft_strjoin(path, "/");
	else
		buf = ft_strdup(path);
	bin = ft_strjoin(buf, file);
	free(buf);
	return (bin);
}

char	*get_absolute_path(t_info *info, t_command *cmd)
{
	char		**path;
	char		**path_temp;
	char		*bin;
	struct stat	buf;

	path = ft_split(env_search(&info->env, "PATH")->value, ':');
	path_temp = path;
	while (*path)
	{
		bin = get_correct_path(*path, cmd->argv[0]);
		if (stat(bin, &buf) == 0)
			break ;
		free(bin);
		bin = 0;
		path++;
	}
	free_2d(path_temp);
	return (bin);
}
