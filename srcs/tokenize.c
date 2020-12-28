/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:05:31 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/27 22:27:43 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void tokenize_quote(t_info *i, char cur, int *flag, char *str)
{
	if (cur == '\'')
	{
		if (*flag & TK_DQOUTE)
			token_update(token_last(i->token), str);
		else if ((*flag & TK_QOUTE) && (*flag & TK_BS_IN_QUOTE))
		{
			*flag &= ~TK_BS_IN_QUOTE;
			token_last(i->token)->str[token_last(i->token)->length - 1] = cur;
		}
		else
			*flag ^= TK_QOUTE;
	}
	else if (cur == '\"')
	{
		if (*flag & TK_QOUTE)
			token_update(token_last(i->token), str);
		else if ((*flag & TK_DQOUTE) && (*flag & TK_BS_IN_QUOTE))
		{
			*flag &= ~TK_BS_IN_QUOTE;
			token_last(i->token)->str[token_last(i->token)->length - 1] = cur;
		}
		else
			*flag ^= TK_DQOUTE;
	}
}

static void tokenize_symbol(t_info *info, char cur, int *flag, char *str)
{
	if (*flag & (TK_QOUTE | TK_DQOUTE))
	{
		if (cur == '\\')
			*flag |= TK_BS_IN_QUOTE;
		else
			*flag &= ~TK_BS_IN_QUOTE;
		token_update(token_last(info->token), str);
	}
	else
	{
		if (cur == '\\')
		{
			if (*flag & TK_BACKSLASH)
				token_update(token_last(info->token), str);
			*flag ^= TK_BACKSLASH;
		}
		else
		{
			if (cur == ';' || cur == '|')
				token_push_back(&info->token, str);
			token_push_back(&info->token, "");
		}
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
		else if (ft_strchr(" \\|;", info->input[i]))
			tokenize_symbol(info, info->input[i], &flag, temp_char);
		else
		{
			flag &= ~TK_BACKSLASH;
			flag &= ~TK_BS_IN_QUOTE;
			token_update(token_last(info->token), temp_char);
		}
	}
	if (flag & (TK_DQOUTE | TK_QOUTE))
		ft_printf("syntax error\n");
	tokenize_delete_empty_token(info);
}
