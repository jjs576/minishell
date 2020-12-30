/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:57:40 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/30 22:15:04 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	t_command *c;
	int i;
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
		replace_input(&info);
		tokenize(&info);
		token_to_command(&info);
		c = info.cmd;
		while (c)
		{
			i = -1;
			ft_printf("%d", c->argc);
			while (++i < c->argc)
				ft_printf(" %s", c->argv[i]);
			ft_printf("\n");
			c = c->next;
		}
	}
	return (0);
}
