/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:44:58 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/21 14:30:39 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# define RETURN_LINE 1
# define RETURN_EOF 0
# define RETURN_ERROR -1

int		check_line(char *str);
int		split_line(char	**str, char **line);
int		get_next_line(int fd, char **line);

size_t	gnl_strlen(char *str);
void	*gnl_memcpy(void *dst, const void *src, size_t n);
char	*gnl_strjoin(char *dst, char *src);
char	*gnl_strndup(char *str, size_t n);
char	*gnl_split(char *str);

#endif
