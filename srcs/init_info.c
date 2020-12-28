/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:43:50 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/28 15:52:36 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_info(t_info *info)
{
	ft_bzero(info, sizeof(t_info));
	info->cmd = ft_calloc(MAX_COMMAND, sizeof(t_command));
}
