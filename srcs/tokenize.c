/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:05:31 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/26 18:49:25 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void tokenize_quote(t_info *info, char cur ,int *flag, char *str)
{
	if (cur == '\'')
	{
		if (*flag & TK_DQOUTE)
			token_update(token_last(info->token), str);
		else
		{
			*flag ^= TK_QOUTE;
			token_push_back(&info->token, "");
		}
	}
	else if (cur == '\"')
	{
		if (*flag & TK_QOUTE)
			token_update(token_last(info->token), str);
		else
		{
			*flag ^= TK_DQOUTE;
			token_push_back(&info->token, "");
		}
	}
}

static void tokenize_space_bs(t_info *info, char cur ,int *flag, char *str)
{
	if (cur == '\\')
	{
		if (*flag & TK_BACKSLASH)
			token_update(token_last(info->token), str);
		*flag ^= TK_BACKSLASH;
	}
	else if (cur == ' ')
	{
		if (*flag & (TK_QOUTE | TK_DQOUTE))
			token_update(token_last(info->token), str);
		else
			token_push_back(&info->token, "");
	}
}
static void	tokenize_delete_empty_token(t_info *info)
{
	int		len;
	t_token	*token;

	len = 0;
	token = info->token;
	while (token)
	{
		len++;
		token = token->next;
	}
	while (len--)
		token_delete(&info->token, "");
}

void 		tokenize(t_info *info)
{
	int i;
	int flag;
	char temp_char[2];

	i = -1;
	temp_char[1] = 0;
	flag = 0;
	info->token = token_new("");
	while (info->input[++i])
	{
		temp_char[0] = info->input[i];
		if (ft_strchr("\'\"", info->input[i]))
			tokenize_quote(info, info->input[i], &flag, temp_char);
		else if (ft_strchr(" \\", info->input[i]))
			tokenize_space_bs(info, info->input[i], &flag, temp_char);
		else
		{
			flag &= ~TK_BACKSLASH;
			token_update(token_last(info->token), temp_char);
		}
	}
	if (flag & (TK_DQOUTE | TK_QOUTE))
		ft_printf("syntax error\n");
	tokenize_delete_empty_token(info);
}
