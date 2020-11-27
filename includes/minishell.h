/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:58:02 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/27 18:39:32 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>

# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

# define MAX_PATH_LENGTH 10000

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env			*env_new(char *key, char *value);
t_env			*env_search(t_env **head, char *key);
void			env_update(t_env **head, char *key, char *value);
void			env_delete(t_env **head, char *key);
void			env_push_back(t_env **head, char *key, char *value);

typedef struct	s_info
{
	t_env	*env;
	char	pwd[MAX_PATH_LENGTH];
	char	oldpwd[MAX_PATH_LENGTH];
}				t_info;

void			init_info(t_info *info);
void			parse_env(t_info *info, char *envp[]);

void			sigint_handler(int signo);
void			sigquit_handler(int signo);

void			prompt(t_info *info);

#endif
