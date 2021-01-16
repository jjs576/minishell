/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:02:09 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 18:26:45 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_new_line(char *str)
{
	char	flag;
	size_t	len;

	len = ft_strlen(str);
	flag = 0;
	while (str[len-- - 1] == '\\')
		flag ^= NL_BACKSLASH;
	return (flag);
}

static char	check_eof(char *s)
{
	char	flag;

	flag = NL_EOF;
	if (ft_strlen(s) == 0)
	{
		ft_printf("exit\n");
		exit(0);
	}
	return (flag);
}

void		prompt(t_info *info)
{
	char	*raw_input;
	int		gnl_ret;
	char	flag;

	flag = NL_BACKSLASH;
	ft_putstr_fd("sh", info->out);
	while (flag)
	{
		if (flag & NL_BACKSLASH)
			ft_putstr_fd("> ", info->out);
		gnl_ret = get_next_line(info->in, &raw_input);
		ft_strlcat(info->input, raw_input, MAX_STR);
		if (gnl_ret == RETURN_LINE)
		{
			flag = check_new_line(raw_input);
			if (flag & NL_BACKSLASH)
				info->input[ft_strlen(info->input) - 1] = 0;
		}
		else if (gnl_ret == RETURN_EOF)
			flag = check_eof(info->input + info->input_len);
		if (gnl_ret == RETURN_LINE)
			info->input_len = ft_strlen(info->input);
	}
}
