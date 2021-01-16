/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 21:18:28 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 22:17:26 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		execute_unforked_builtin(t_info *info, t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(info, cmd);
	else
		return (0);
	return (1);
}

static int		execute_builtin(t_info *info, t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(info);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(info, cmd);
	else
		return (0);
	return (1);
}

static void		execute_child(t_info *info, t_command *cmd)
{
	char		**envp;
	char		*path;
	struct stat	buf;

	envp = get_env_array(info);
	if ((path = get_absolute_path(info, cmd)) == 0)
	{
		path = cmd->argv[0];
		if (stat(path, &buf) != 0)
		{
			ft_putstr_fd("sh: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	if (execve(path, cmd->argv, envp) == -1)
	{
		print_error(cmd->argv[0], errno);
		exit(errno);
	}
}

void			execute(t_info *info)
{
	t_command	*cmd;
	pid_t		pid;
	int			index;

	index = 0;
	cmd = info->cmd;
	while (cmd && cmd->argc > 0 && (++index | 1))
	{
		pipe(info->pipefd[index]);
		if (!execute_unforked_builtin(info, cmd))
		{
			pid = fork();
			if (pid == 0 && connect_fd(cmd, info->pipefd, index))
			{
				if (!execute_builtin(info, cmd))
					execute_child(info, cmd);
			}
			else
				cmd->pid = pid;
		}
		close_fd(info->pipefd[index - 1][0]);
		close_fd(info->pipefd[index][1]);
		cmd = cmd->next;
	}
	wait_forked(info);
}
