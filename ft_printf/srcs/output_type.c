/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 23:06:22 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:02:42 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	output(t_printf *info)
{
	if (info->flag & F_CHAR)
		output_char(info, va_arg(info->arg, int));
	else if (info->flag & F_STR)
		output_string(info, va_arg(info->arg, char *));
	else if (info->flag & F_INT)
		output_int(info);
	else if (info->flag & F_HEX)
		output_hex(info);
	else if (info->flag & F_PERCENT)
		output_char(info, '%');
}

void	output_char(t_printf *info, char c)
{
	info->padding = ftpf_max(info->width - 1, 0);
	padding(info, FRONT);
	ftpf_putchar(info, c);
	padding(info, BACK);
}

void	output_string(t_printf *info, char *s)
{
	int	len;

	if (!s)
		s = STR_NULL;
	len = ftpf_strlen(s);
	if (info->flag & F_PRECISION && info->precision >= 0)
		len = ftpf_min(len, info->precision);
	info->padding = ftpf_max(info->width - len, 0);
	padding(info, FRONT);
	ftpf_putstr(info, s, len);
	padding(info, BACK);
}

void	output_int(t_printf *info)
{
	unsigned long long	num;
	char				buf[32];
	char				*s;

	if (info->flag & F_LL)
		!(info->flag & F_UNSIGNED) ? (num = va_arg(info->arg, long long))
		: (num = va_arg(info->arg, unsigned long long));
	else if (info->flag & F_L)
		!(info->flag & F_UNSIGNED) ? (num = va_arg(info->arg, long))
		: (num = va_arg(info->arg, unsigned long));
	else if (info->flag & F_HH)
		!(info->flag & F_UNSIGNED) ? (num = (char)va_arg(info->arg, int))
		: (num = (unsigned char)va_arg(info->arg, int));
	else if (info->flag & F_H)
		!(info->flag & F_UNSIGNED) ? (num = (short)va_arg(info->arg, int))
		: (num = (unsigned short)va_arg(info->arg, int));
	else
		!(info->flag & F_UNSIGNED) ? (num = va_arg(info->arg, int))
		: (num = va_arg(info->arg, unsigned int));
	s = num_to_string(buf, 32, (unsigned long long)num, info->flag);
	if ((info->flag & F_PRECISION) && info->precision == 0 && num == 0)
		s[((info->flag & F_PLUS) || (info->flag & F_SPACE)) ? 1 : 0] = 0;
	print_int(info, s, ftpf_strlen(s));
}

void	output_hex(t_printf *info)
{
	unsigned long long	num;
	char				buf[32];
	char				*s;

	if (info->flag & F_LL)
		num = va_arg(info->arg, unsigned long long);
	else if (info->flag & F_L)
		num = va_arg(info->arg, unsigned long);
	else if (info->flag & F_HH)
		num = (unsigned char)va_arg(info->arg, unsigned int);
	else if (info->flag & F_H)
		num = (unsigned short)va_arg(info->arg, unsigned int);
	else
		num = va_arg(info->arg, unsigned int);
	if (!(info->flag & F_POINTER) && num == 0)
		info->flag &= ~F_ALT;
	s = hex_to_string(buf, 32, num, info->flag);
	if ((info->flag & F_PRECISION) && info->precision == 0 && num == 0)
		s[info->flag & F_ALT ? 2 : 0] = 0;
	print_hex(info, s, ftpf_strlen(s), ((info->flag & F_CAPS) ? "0X" : "0x"));
}
