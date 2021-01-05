/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 21:18:28 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/05 21:21:57 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(t_info *info, t_command *cmd)
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

void	execute_bin(t_info *info, t_command *cmd)
{
	char	**envp;
	char	*path;

	envp = get_env_array(info);
	path = env_search(&info->env, "PATH")->value;

}

