/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:05:37 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/14 22:53:42 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > -1)
		close(fd);
}

void	free_2d(char **p)
{
	char	**temp;

	temp = p;
	while (*temp)
		free(*temp++);
	free(p);
}

void	init_info(t_info *info)
{
	ft_bzero(info, sizeof(t_info));
}

void	clear_info(t_info *info)
{
	t_token		*temp_token;
	t_token		*token;
	t_command	*temp_cmd;
	t_command	*cmd;

	token = info->token;
	while (token)
	{
		temp_token = token;
		token = token->next;
		free(temp_token->str);
		free(temp_token);
	}
	cmd = info->cmd;
	while (cmd)
	{
		temp_cmd = cmd;
		cmd = cmd->next;
		free_2d(temp_cmd->argv);
		free(temp_cmd);
	}
}
