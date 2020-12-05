/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:44:58 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/05 16:24:46 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>


# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# define RETURN_LINE 1
# define RETURN_EOF 0
# define RETURN_ERROR -1

int		get_next_line(int fd, char **line);

#endif
