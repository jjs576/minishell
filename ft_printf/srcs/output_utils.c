/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 21:46:16 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:02:59 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ftpf_max(int a, int b)
{
	return (a > b ? a : b);
}

int		ftpf_min(int a, int b)
{
	return (a < b ? a : b);
}

void	ftpf_putstr(t_printf *info, char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (s[i] && i < len)
	{
		ftpf_putchar(info, s[i]);
		i++;
	}
}

void	ftpf_putchars(t_printf *info, char c, int n)
{
	while (n--)
		ftpf_putchar(info, c);
}

void	padding(t_printf *info, int n)
{
	char	c;

	if (!info->padding)
		return ;
	c = (info->flag & F_ZERO) ? '0' : ' ';
	if (!n && !(info->flag & F_MINUS))
		while (info->padding-- > 0)
			ftpf_putchar(info, c);
	else if (n && (info->flag & F_MINUS))
		while (info->padding-- > 0)
			ftpf_putchar(info, c);
}
