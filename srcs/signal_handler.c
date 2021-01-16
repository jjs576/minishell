/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:35:30 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 18:46:35 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info		*signal_info(t_info *input)
{
	static t_info	*info;

	if (input)
		info = input;
	return (info);
}

static void	sigint(t_info *info)
{
	if (info->status & INFO_WAITING)
		ft_printf("\b\b");
	else
	{
		info->returned = 1;
		init_info_input(info);
		clear_info(info);
		ft_printf("\b\b  \nsh> ");
	}
}

static void	sigquit(t_info *info)
{
	ft_printf("\b\b  \b\b");
	if (info->status & INFO_WAITING)
		ft_printf("\b\b^\\Quit: 3\n");
}

void		signal_handler(int signo)
{
	t_info	*info;

	info = signal_info(0);
	if (signo == SIGINT)
		sigint(info);
	else if (signo == SIGQUIT)
		sigquit(info);
}
