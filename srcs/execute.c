/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 21:18:28 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/14 23:36:00 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin(t_info *info, t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(info, cmd);
	/*else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(info, cmd);*/
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(info);
	/*else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(info, cmd);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(info, cmd);*/
	else
		return (0);
	return (1);
}

static char		*get_correct_path(char *path, char *file)
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

static char		*get_absolute_path(t_info *info, t_command *cmd)
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

static void		execute_child(t_info *info, t_command *cmd)
{
	char	**envp;
	char	*path;

	envp = get_env_array(info);
	if ((path = get_absolute_path(info, cmd)) == 0)
		path = cmd->argv[0];
	if (execve(path, cmd->argv, envp) == -1)
	{
		print_error(cmd->argv[0], errno);
	}
	exit(0);
}

void		execute(t_info *info)
{
	t_command	*cmd;
	pid_t		pid;
	int			index;

	index = -1;
	cmd = info->cmd;
	while (cmd && (++index | 1))
	{
		pipe(info->pipefd[index]);
		pid = fork();
		if (pid == 0)
		{
			connect_fd(cmd, info->pipefd, index);
			if (!execute_builtin(info, cmd))
				execute_child(info, cmd);
		}
		else
			cmd->pid = pid;
		if (index > 0)
			close_fd(info->pipefd[index - 1][0]);
		close_fd(info->pipefd[index][1]);
		cmd = cmd->next;
	}
	wait_forked(info);
}
