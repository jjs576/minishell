/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:35:30 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/27 16:37:17 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			sigint_handler(int signo)
{
	(void)signo;
}

void			sigquit_handler(int signo)
{
	(void)signo;
}
