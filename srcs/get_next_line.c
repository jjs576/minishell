/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:46:06 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/29 23:11:05 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		get_next_line(int fd, char **line)
{
	char	buf[1];
	char	*save;
	int		count;
	int		flag;
	char	*temp;

	if (!line)
		return (RETURN_ERROR);
	save = ft_calloc(10000, sizeof(char));
	count = 0;
	while ((flag = read(fd, buf, 1)) >= 0)
	{
		if (buf[0] == '\n' || flag == 0)
			break ;
		save[count++] = buf[0];
		save[count] = 0;
	}
	temp = ft_calloc(count + 1, sizeof(char));
	ft_memcpy(temp, save, count);
	temp[count] = 0;
	*line = temp;
	free(save);
	return (flag);
}
