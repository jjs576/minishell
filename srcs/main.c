/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:57:40 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/28 16:09:34 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	t_command *c;

	(void)argc;
	(void)argv;
	init_info(&info);
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, (void *)sigquit_handler);
	parse_env(&info, envp);
	while (1)
	{
		ft_bzero(&info.input, MAX_STR);
		info.input_len = 0;
		prompt(&info);
		tokenize(&info);
		token_to_command(&info);
		c = info.cmd;
		while (c)
		{
			ft_printf("%d %s\n",c->flag, c->argv[0]);
			c = c->next;
		}
	}
	return (0);
}
