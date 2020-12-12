/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 00:07:15 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/12 18:37:08 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token			*token_new(char *str)
{
	t_token		*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	new_token->str = ft_strdup(str);
	return (new_token);
}

t_token			*token_last(t_token *head)
{
	if (!head)
		return (0);
	while (head->next)
		head = head->next;
	return (head);
}

void			token_update(t_token *token, char *str)
{
	char	*temp;

	if (!token)
		return ;
	temp = token->str;
	token->str = ft_strjoin(token->str, str);
	if (temp)
		free(temp);
}

void			token_push_back(t_token **head, char *str)
{
	t_token		*token;

	if (!*head)
		*head = token_new(str);
	else
	{
		token = *head;
		while (token->next)
			token = token->next;
		token->next = token_new(str);
	}
}

void			token_delete(t_token **head, char *str)
{
	t_token	*token;
	t_token	*erase;

	token = *head;
	if (!ft_strcmp(token->str, str))
	{
		*head = (*head)->next;
		free(token->str);
		free(token);
		return ;
	}
	while (token->next)
	{
		if (token->next && !ft_strcmp(token->next->str, str))
		{
			erase = token->next;
			token->next = token->next->next;
			free(erase->str);
			free(erase);
			return ;
		}
		token = token->next;
	}
}
