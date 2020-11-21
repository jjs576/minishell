/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:46:06 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:30:42 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_line(char *str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		if (*str == '\n')
			return (ret);
		ret++;
		str++;
	}
	return (-1);
}

int		split_line(char **str, char **line)
{
	int		i;
	char	*temp;

	if ((i = check_line(*str)) >= 0)
	{
		*line = gnl_strndup(*str, i);
		temp = *str;
		*str = gnl_strndup(temp + i + 1, gnl_strlen(temp) - i - 1);
		free(temp);
		return (RETURN_LINE);
	}
	else
	{
		*line = gnl_strndup(*str, gnl_strlen(*str));
		free(*str);
		*str = 0;
		return (RETURN_EOF);
	}
}

int		get_next_line(int fd, char **line)
{
	int			count;
	char		*buf;
	static char	*save[OPEN_MAX];
	char		*temp;

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (RETURN_ERROR);
	if (!(buf = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (RETURN_ERROR);
	while ((count = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[count] = 0;
		temp = save[fd];
		save[fd] = gnl_strjoin(temp, buf);
		free(temp);
		temp = 0;
		if (check_line(save[fd]) >= 0 || count == 0)
			break ;
	}
	free(buf);
	buf = 0;
	if (count == -1)
		return (RETURN_ERROR);
	return (split_line(&save[fd], line));
}
