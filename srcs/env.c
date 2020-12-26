/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:11:33 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/26 19:11:59 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*ret;

	if (!(ret = (t_env *)ft_calloc(1, sizeof(t_env))))
		exit(1);
	ret->key = ft_strdup(key);
	if (value)
		ret->value = ft_strdup(value);
	return (ret);
}

t_env	*env_search(t_env **head, char *key)
{
	t_env	*env;

	env = *head;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (0);
}

void	env_update(t_env **head, char *key, char *value)
{
	t_env	*env;

	env = env_search(head, key);
	if (!env)
		env_push_back(head, key, value);
	else
	{
		if (env->value)
			free(env->value);
		env->value = ft_strdup(value);
	}
}

void	env_delete(t_env **head, char *key)
{
	t_env	*env;
	t_env	*erase;

	env = *head;
	if (!ft_strcmp(env->key, key))
	{
		*head = (*head)->next;
		free(env->key);
		free(env->value);
		free(env);
		return ;
	}
	while (env->next)
	{
		if (env->next && !ft_strcmp(env->next->key, key))
		{
			erase = env->next;
			env->next = env->next->next;
			free(erase->key);
			free(erase->value);
			free(erase);
			return ;
		}
		env = env->next;
	}
}

void	env_push_back(t_env **head, char *key, char *value)
{
	t_env	*env;

	if (!*head)
		*head = env_new(key, value);
	else
	{
		env = *head;
		while (env->next)
			env = env->next;
		env->next = env_new(key, value);
	}
}
