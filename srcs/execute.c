/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 21:18:28 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/07 21:58:46 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin(t_info *info, t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(info, cmd);
	else
		return (0);
	return (1);
}

static void	execute_child(t_info *info, t_command *cmd)
{
	char	**envp;
	char	*path;

	envp = get_env_array(info);
	path = env_search(&info->env, "PATH")->value;

}

static void	connect_fd(t_command *cmd1, t_command *cmd2, int fd[2])
{
	if (cmd1->fd_in == -1)
		dup2(cmd1->fd_in, 0);
	else
		cmd1->fd_in = dup(STDIN);
	if (cmd1->fd_out == -1)
		dup2(cmd1->fd_out, 1);
	else
		cmd1->fd_out = dup(STDOUT);
	if (cmd2)
	{
		dup2(fd[0], cmd1->fd_out);
		dup2(fd[1], cmd2->fd_in);
	}
}

static void	wait_forked(t_info *info)
{
	t_command	*cmd;
	int			status;

	cmd = info->cmd;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
}

void		execute(t_info *info)
{
	t_command	*cmd;
	t_command	*next;
	pid_t		pid;
	int			pipefd[2];

	cmd = info->cmd;
	while (cmd)
	{
		next = 0;
		pipe(pipefd);
		if (!(cmd->flag & CMD_END) && cmd->next)
			next = cmd->next;
		pid = fork();
		if (pid == 0) // child
		{
			connect_fd(cmd, next, pipefd);
			execute_child(info, cmd);
		}
		else	// parent
		{
			cmd->pid = pid;
		}
		cmd = cmd->next;
	}
	wait_forked(info);
}
