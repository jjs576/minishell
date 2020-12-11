/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:58:02 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/11 21:34:34 by jjoo             ###   ########.fr       */
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

# define MAX_PATH_LENGTH	10000
# define MAX_STR			10000

# define ASC_NEW_LINE		10

# define NL_BACKSLASH		(1 << 0)
# define NL_EOF				(1 << 1)

# define TK_DQOUTE			(1 << 0)
# define TK_QOUTE			(1 << 1)
# define TK_PIPE			(1 << 2)
# define TK_SCOLON			(1 << 3)

typedef struct	s_token
{
	char			*str;
	int				flag;
	struct s_token	*next;
}				t_token;

t_token			*token_new(char *str);
t_token			*token_last(t_token **head);
void			token_update(t_token **head, char *key, char *value);
void			token_delete(t_token **head, char *str);
void			token_push_back(t_token **head, char *str);

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
	t_token	*token;
	char	pwd[MAX_PATH_LENGTH];
	char	oldpwd[MAX_PATH_LENGTH];
	char	input[MAX_STR];
	int		input_len;
}				t_info;

void			init_info(t_info *info);
void			parse_env(t_info *info, char *envp[]);

void			sigint_handler(int signo);
void			sigquit_handler(int signo);

void			prompt(t_info *info);
void			tokenize(t_info *info);

#endif
