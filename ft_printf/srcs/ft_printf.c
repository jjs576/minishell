/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 20:35:13 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:07:15 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char *format, ...)
{
	t_printf	info;

	ftpf_memset(&info, 0, sizeof(info));
	info.count = 0;
	info.format = (char *)format;
	va_start(info.arg, format);
	while (*info.format)
	{
		if (*info.format == '%')
		{
			info.format++;
			if (!*info.format)
				break ;
			parse_format(&info);
		}
		else
			ftpf_putchar(&info, *info.format++);
		if (info.error)
			return (0);
	}
	va_end(info.arg);
	return (info.count);
}
