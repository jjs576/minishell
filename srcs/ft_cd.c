/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:09:14 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 13:57:21 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_dir(t_info *info, char *dir)
{
	char	*buf;
	int		ret;

	if (ft_strcmp(dir, "~") == 0)
		buf = ft_strdup(env_search(&info->env, "HOME")->value);
	else
		buf = ft_strdup(dir);
	ret = chdir(buf);
	free(buf);
	return (ret);
}

void		ft_cd(t_info *info, t_command *cmd)
{
	char	buf[MAX_PATH_LENGTH];
	char	pwd[MAX_PATH_LENGTH];

	ft_strlcat(pwd, env_search(&info->env, "PWD")->value, MAX_PATH_LENGTH);
	if (cmd->argc == 1)
		ft_strlcat(buf, "~", MAX_STR);
	else
		ft_strlcat(buf, cmd->argv[1], MAX_STR);
	if (change_dir(info, buf) == -1)
	{
		print_error(cmd->argv[0], errno);
		info->returned = 1;
	}
	else
	{
		env_update(&info->env, "OLDPWD", pwd);
		ft_bzero(pwd, sizeof(MAX_PATH_LENGTH));
		getcwd(pwd, MAX_PATH_LENGTH);
		env_update(&info->env, "PWD", pwd);
		info->returned = 0;
	}
}
