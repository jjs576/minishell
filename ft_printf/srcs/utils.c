/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 21:05:07 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:03:35 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ftpf_putchar(t_printf *info, char c)
{
	write(1, &c, 1);
	info->count++;
}

int		ftpf_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i] != (char)c)
		if (!s[i])
			return (-1);
	return (i);
}

int		ftpf_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

size_t	ftpf_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ftpf_memset(void *b, int c, size_t len)
{
	unsigned char	*uc;

	uc = b;
	while (len > 0)
	{
		*uc++ = (unsigned char)c;
		len--;
	}
	return (b);
}
