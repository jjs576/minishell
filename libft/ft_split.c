/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 16:50:58 by jjoo              #+#    #+#             */
/*   Updated: 2020/07/09 17:22:54 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		cnt_word(char *str, char c)
{
	int	can_word;
	int	word_count;

	word_count = 0;
	can_word = 0;
	while (*str)
	{
		if (*str == c)
		{
			if (can_word)
				word_count++;
			can_word = 0;
		}
		else
			can_word = 1;
		str++;
	}
	if (can_word)
		word_count++;
	return (word_count);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dup;

	i = 0;
	if (!(dup = ft_calloc(sizeof(char), n + 1)))
		return (0);
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		len;
	int		i;

	if (!s)
		return (0);
	if (!(ret = (char**)ft_calloc(sizeof(char*), (cnt_word((char*)s, c) + 1))))
		return (0);
	len = 0;
	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (len != 0)
				ret[i++] = ft_strndup((char*)s - len, len);
			len = 0;
		}
		else
			len++;
		s++;
	}
	if (len != 0)
		ret[i++] = ft_strndup((char*)s - len, len);
	return (ret);
}
