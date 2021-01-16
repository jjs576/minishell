/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:05:31 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 20:21:06 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokenize_quote(t_info *i, char cur, int *flag, char *str)
{
	if (*flag & TK_BACKSLASH)
		token_update(token_last(i->token), str);
	else if ((cur == '\'' && *flag & TK_DQOUTE) ||
		(cur == '\"' && *flag & TK_QOUTE))
		token_update(token_last(i->token), str);
	else if (cur == '\"' && (*flag & TK_DQOUTE) && (*flag & TK_BS_IN_QUOTE))
	{
		*flag &= ~TK_BS_IN_QUOTE;
		token_last(i->token)->str[token_last(i->token)->length - 1] = cur;
	}
	else
	{
		if (cur == '\'')
			*flag ^= TK_QOUTE;
		else
			*flag ^= TK_DQOUTE;
	}
	*flag &= (~TK_BACKSLASH & ~TK_BS_IN_QUOTE);
}

static void	tokenize_symbol(t_info *info, char cur, int *flag, char *str)
{
	if (*flag & (TK_QOUTE | TK_DQOUTE))
	{
		if (cur == '\\')
			*flag |= TK_BS_IN_QUOTE;
		else
			*flag &= ~TK_BS_IN_QUOTE;
		token_update(token_last(info->token), str);
		return ;
	}
	if (cur == '\\')
	{
		if (*flag & TK_BACKSLASH)
			token_update(token_last(info->token), str);
		*flag ^= TK_BACKSLASH;
	}
	else
	{
		if (cur == ';')
			token_push_back(&info->token, str, TK_END);
		else if (cur == '|')
			token_push_back(&info->token, str, TK_PIPE);
		else if (cur == '<' || cur == '>')
			token_push_back(&info->token, str, TK_REDIR);
		token_push_back(&info->token, "", 0);
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

static void	tokenize_merge_redirect_symbol(t_info *info)
{
	t_token	*token;
	t_token	*next;
	char	*temp;

	token = info->token;
	while (token)
	{
		if (token->flag & TK_REDIR)
		{
			next = token->next;
			while (next && token->flag == next->flag)
			{
				temp = ft_strjoin(token->str, token->next->str);
				free(token->str);
				token->str = temp;
				token->length = ft_strlen(token->str);
				free(token->next->str);
				token->next = next->next;
				free(next);
				next = token->next;
			}
		}
		token = token->next;
	}
}

void		tokenize(t_info *info)
{
	int		i;
	int		flag;
	char	temp_char[2];

	i = -1;
	temp_char[1] = 0;
	flag = 0;
	info->token = token_new("", 0);
	while (info->input[++i])
	{
		temp_char[0] = info->input[i];
		if (ft_strchr("\'\"", info->input[i]))
			tokenize_quote(info, info->input[i], &flag, temp_char);
		else if (ft_strchr(" \\|;<>", info->input[i]))
			tokenize_symbol(info, info->input[i], &flag, temp_char);
		else
		{
			flag &= (~TK_BACKSLASH & ~TK_BS_IN_QUOTE);
			token_update(token_last(info->token), temp_char);
		}
	}
	if (flag & (TK_DQOUTE | TK_QOUTE))
		ft_putendl_fd("syntax error", 2);
	tokenize_delete_empty_token(info);
	tokenize_merge_redirect_symbol(info);
}
