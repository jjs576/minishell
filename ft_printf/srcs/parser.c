/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:30:26 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:07:29 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flag(t_printf *info)
{
	while (ftpf_strchr("+-0 #", *info->format) > -1)
	{
		if (*info->format == '+')
			info->flag |= F_PLUS;
		else if (*info->format == '-')
			info->flag |= F_MINUS;
		else if (*info->format == ' ')
			info->flag |= F_SPACE;
		else if (*info->format == '#')
			info->flag |= F_ALT;
		else if (*info->format == '0')
			info->flag |= F_ZERO;
		info->format++;
	}
}

static void	parse_width(t_printf *info)
{
	if (*info->format == '*')
	{
		if ((info->width = va_arg(info->arg, int)) < 0)
		{
			info->flag |= F_MINUS;
			info->width *= -1;
		}
		info->format++;
	}
	else if (ftpf_isdigit(*info->format))
		while (ftpf_isdigit(*info->format))
		{
			info->width = info->width * 10 + *info->format - '0';
			info->format++;
		}
}

static void	parse_precision(t_printf *info)
{
	if (*info->format != '.')
		return ;
	info->format++;
	info->flag |= F_PRECISION;
	if (*info->format == '*')
	{
		info->precision = va_arg(info->arg, int);
		if (info->precision < 0)
			info->flag &= ~F_PRECISION;
		info->format++;
	}
	else if (ftpf_isdigit(*info->format))
	{
		while (ftpf_isdigit(*info->format))
		{
			info->precision = info->precision * 10 + *info->format - '0';
			info->format++;
		}
	}
}

static void	parse_specifier(t_printf *info)
{
	const int	formats[] = {
		F_CHAR, F_STR, F_HEX | F_L | F_ALT | F_POINTER, F_INT,
		F_INT, F_UNSIGNED | F_INT, F_HEX, F_HEX | F_CAPS, F_PERCENT
	};

	while (ftpf_strchr("lh", *info->format) > -1)
	{
		if (*info->format == 'h')
			info->flag |= (info->flag & F_H ? F_HH : F_H);
		else if (*info->format == 'l')
			info->flag |= (info->flag & F_L ? F_LL : F_L);
		info->format++;
	}
	if (ftpf_strchr(FORMATS, *info->format) > -1)
	{
		info->flag |= formats[ftpf_strchr(FORMATS, *info->format)];
		info->format++;
	}
}

void		parse_format(t_printf *info)
{
	int	f;

	info->flag = 0;
	info->width = 0;
	info->precision = 0;
	parse_flag(info);
	parse_width(info);
	parse_precision(info);
	parse_specifier(info);
	f = info->flag;
	if (!(f & F_CHAR) && !(f & F_STR) && !(f & F_INT)
	&& !(f & F_HEX) && !(f & F_PERCENT))
	{
		info->error = 1;
		return ;
	}
	if (info->flag & F_ZERO && info->flag & F_MINUS)
		info->flag &= ~F_ZERO;
	if (info->flag & F_PLUS)
		info->flag &= ~F_SPACE;
	if (!(info->flag & F_PERCENT) && info->flag & F_PRECISION)
		info->flag &= ~F_ZERO;
	output(info);
}
