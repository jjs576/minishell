/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:57:40 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/12 16:35:19 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char*argv[], char *envp[])
{
	t_info	info;

	t_token	*token;
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
		token = info.token;
		while (token){
			ft_printf("%s\n", token->str);
			token = token->next;
		}
	}
	return (0);
}
