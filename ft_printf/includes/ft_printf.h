/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 20:31:20 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:37:15 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUF_SIZE		256

# define F_L			0x00000001
# define F_LL			0x00000002
# define F_H			0x00000004
# define F_HH			0x00000008

# define F_PLUS			0x00000010
# define F_MINUS		0x00000020
# define F_ALT			0x00000040
# define F_CAPS			0x00000080

# define F_SPACE		0x00000100
# define F_ZERO			0x00000200
# define F_CHAR			0x00000400
# define F_STR			0x00000800

# define F_INT			0x00001000
# define F_HEX			0x00002000
# define F_PERCENT		0x00004000
# define F_UNSIGNED		0x00008000

# define F_PRECISION	0x00010000
# define F_POINTER		0x00020000

# define STR_NULL		"(null)"
# define FRONT			0
# define BACK			1

# define HEX "0123456789abcdef"
# define HEX_CAPS "0123456789ABCDEF"
# define FORMATS "cspdiuxX%"

typedef struct	s_printf
{
	int		flag;
	int		width;
	int		precision;
	char	*format;
	int		count;
	va_list	arg;
	int		padding;
	int		error;
}				t_printf;

int				ft_printf(const char *format, ...);
void			parse_format(t_printf *info);
void			output(t_printf *info);

char			*num_to_string(char *buf, int size,
								unsigned long long n, int flag);
char			*hex_to_string(char *buf, int size,
								unsigned long long n, int flag);
void			print_int(t_printf *info, char *s, int len);
void			print_hex(t_printf *info, char *s, int len, char *sign);

void			output_char(t_printf *info, char c);
void			output_string(t_printf *info, char *s);
void			output_int(t_printf *info);
void			output_hex(t_printf *info);

int				ftpf_max(int a, int b);
int				ftpf_min(int a, int b);
void			ftpf_putstr(t_printf *info, char *s, size_t len);
void			ftpf_putchars(t_printf *info, char c, int n);
void			padding(t_printf *info, int n);

int				ftpf_strchr(const char *s, int c);
size_t			ftpf_strlen(const char *s);
void			*ftpf_memset(void *b, int c, size_t len);
int				ftpf_isdigit(char c);
void			ftpf_putchar(t_printf *info, char c);

#endif
