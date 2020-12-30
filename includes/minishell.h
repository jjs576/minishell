/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:58:02 by jjoo              #+#    #+#             */
/*   Updated: 2020/12/30 21:35:37 by jjoo             ###   ########.fr       */
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

# define MAX_PATH_LENGTH	1000
# define MAX_STR			1000
# define MAX_COMMAND		100

# define ASC_NEW_LINE		10

# define NL_BACKSLASH		(1 << 0)
# define NL_EOF				(1 << 1)

# define TK_DQOUTE			(1 << 0)
# define TK_QOUTE			(1 << 1)
# define TK_PIPE			(1 << 2)
# define TK_BACKSLASH		(1 << 3)
# define TK_BS_IN_QUOTE		(1 << 4)

# define CMD_PIPE			(1 << 0);
# define CMD_SEMIC			(1 << 1);

typedef struct	s_token
{
	char			*str;
	int				flag;
	int				length;
	struct s_token	*next;
}				t_token;

t_token			*token_new(char *str);
t_token			*token_last(t_token *head);
void			token_update(t_token *last, char *str);
void			token_push_back(t_token **head, char *str);
void			token_delete(t_token **head, char *str);

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

typedef struct	s_command
{
	int					argc;
	char 				argv[MAX_STR][MAX_STR];
	int					flag;
	int					fd_read;
	int					fd_write;
	struct s_command	*next;
}				t_command;

t_command		*cmd_new();
void			cmd_update(t_command *cmd, char *str);
t_command		*cmd_last(t_command *head);
void			cmd_push_back(t_command **head);

typedef struct	s_info
{
	t_env		*env;
	t_token		*token;
	t_command	*cmd;
	char		pwd[MAX_PATH_LENGTH];
	char		oldpwd[MAX_PATH_LENGTH];
	char		input[MAX_STR];
	int			input_len;
	int			command_num;
	int			returned;
}				t_info;

void			init_info(t_info *info);
void			parse_env(t_info *info, char *envp[]);

void			sigint_handler(int signo);
void			sigquit_handler(int signo);

void			prompt(t_info *info);
void			replace_input(t_info *info);
void			tokenize(t_info *info);
void			token_to_command(t_info *info);

#endif
