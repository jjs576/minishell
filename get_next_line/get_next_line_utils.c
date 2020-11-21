/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 10:47:19 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:29:54 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	void		*ret;
	char		*cdst;
	const char	*csrc;

	if (!dst && !src)
		return (0);
	ret = dst;
	cdst = (char *)dst;
	csrc = (char *)src;
	while (n--)
		*cdst++ = *csrc++;
	return (ret);
}

char	*gnl_strjoin(char *dst, char *src)
{
	char	*ret;
	size_t	len_dst;
	size_t	len_src;

	len_src = gnl_strlen(src);
	if (!dst)
		return ((ret = gnl_strndup(src, len_src)));
	len_dst = gnl_strlen(dst);
	if (!(ret = (char*)malloc(sizeof(char) * (len_dst + len_src + 1))))
		return (0);
	ret[0] = 0;
	gnl_memcpy(ret, dst, len_dst);
	gnl_memcpy(ret + len_dst, src, len_src);
	ret[len_dst + len_src] = 0;
	return (ret);
}

char	*gnl_strndup(char *str, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	if (!(dup = (char*)malloc(sizeof(char) * n + 1)))
		return (0);
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
