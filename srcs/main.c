/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:57:40 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/27 18:44:07 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char*argv[], char *envp[])
{
	t_info	info;

	(void)argc;
	(void)argv;
	init_info(&info);
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, (void *)sigquit_handler);
	parse_env(&info, envp);
	prompt(&info);
	return (0);
}
