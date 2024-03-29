/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:57:40 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 21:44:21 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;

	(void)argc;
	(void)argv;
	init_info(&info);
	signal_info(&info);
	signal(SIGINT, (void *)signal_handler);
	signal(SIGQUIT, (void *)signal_handler);
	parse_env(&info, envp);
	while (!(info.status & INFO_EXIT))
	{
		init_info_input(&info);
		prompt(&info);
		replace_input(&info);
		tokenize(&info);
		token_to_command(&info);
		handle_fd(&info);
		if (!(info.status & INFO_DONT_EXEC))
			execute(&info);
		clear_info(&info);
	}
	return (info.exit_return);
}
