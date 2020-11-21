/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:14:39 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:02:23 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*num_to_string(char *buf, int size, unsigned long long n, int flag)
{
	int	pos;
	int	negative;

	negative = 0;
	pos = size;
	if (!(flag & F_UNSIGNED) && (long long)n < 0)
	{
		negative = 1;
		n = -n;
	}
	buf[--pos] = 0;
	while (n >= 10)
	{
		buf[--pos] = n % 10 + '0';
		n /= 10;
	}
	buf[--pos] = n + '0';
	if (negative)
		buf[--pos] = '-';
	else if (flag & F_PLUS)
		buf[--pos] = '+';
	else if (flag & F_SPACE)
		buf[--pos] = ' ';
	return (&buf[pos]);
}

char	*hex_to_string(char *buf, int size, unsigned long long n, int flag)
{
	int			pos;
	const char	*base = flag & F_CAPS ? HEX_CAPS : HEX;

	pos = size;
	buf[--pos] = 0;
	buf[--pos] = base[n % 16];
	n /= 16;
	while (n != 0)
	{
		buf[--pos] = base[n % 16];
		n /= 16;
	}
	if (flag & F_ALT)
	{
		buf[--pos] = (flag & F_CAPS) ? 'X' : 'x';
		buf[--pos] = '0';
	}
	return (&buf[pos]);
}

void	print_int(t_printf *info, char *s, int len)
{
	int		precision;
	int		width;
	char	sign;

	sign = (ftpf_strchr("- +", s[0]) > -1) ? s[0] : 0;
	len -= (sign ? 1 : 0);
	width = info->width - ftpf_max(len, info->precision);
	width = ftpf_max(0, width - (sign ? 1 : 0));
	precision = ftpf_max(0, info->precision - len);
	if (info->flag & F_ZERO)
	{
		(sign ? ftpf_putchar(info, sign) : 0);
		if (!(info->flag & F_MINUS))
			ftpf_putchars(info, '0', width);
	}
	else
	{
		if (!(info->flag & F_MINUS))
			ftpf_putchars(info, ' ', width);
		(sign ? ftpf_putchar(info, sign) : 0);
	}
	ftpf_putchars(info, '0', precision);
	ftpf_putstr(info, s + (sign ? 1 : 0), len);
	if (info->flag & F_MINUS)
		ftpf_putchars(info, ' ', width);
}

void	print_hex(t_printf *info, char *s, int len, char *sign)
{
	int		precision;
	int		width;

	len -= (info->flag & F_ALT ? 2 : 0);
	width = info->width - ftpf_max(len, info->precision);
	width = ftpf_max(0, width - (info->flag & F_ALT ? 2 : 0));
	precision = ftpf_max(0, info->precision - len);
	if (info->flag & F_ZERO)
	{
		(info->flag & F_ALT ? ftpf_putstr(info, sign, 2) : 0);
		if (!(info->flag & F_MINUS))
			ftpf_putchars(info, '0', width);
	}
	else
	{
		if (!(info->flag & F_MINUS))
			ftpf_putchars(info, ' ', width);
		(info->flag & F_ALT ? ftpf_putstr(info, sign, 2) : 0);
	}
	ftpf_putchars(info, '0', precision);
	ftpf_putstr(info, s + (info->flag & F_ALT ? 2 : 0), len);
	if (info->flag & F_MINUS)
		ftpf_putchars(info, ' ', width);
}
