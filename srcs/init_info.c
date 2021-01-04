/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:43:50 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/04 22:30:34 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_info(t_info *info)
{
	ft_bzero(info, sizeof(t_info));
	info->in = dup(STDIN);
	info->out = dup(STDOUT);
}
