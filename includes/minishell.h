/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:58:02 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/07 21:57:47 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

# define MAX_PATH_LENGTH	1000
# define MAX_STR			1000
# define MAX_COMMAND		100

# define STDIN				0
# define STDOUT				1

# define NL_BACKSLASH		0x00000001
# define NL_EOF				0x00000002

# define TK_DQOUTE			0x00000001
# define TK_QOUTE			0x00000002
# define TK_PIPE			0x00000004
# define TK_BACKSLASH		0x00000008
# define TK_BS_IN_QUOTE		0x00000010
# define TK_REDIR			0x00000020
# define TK_END				0x00000040

# define CMD_PIPE			0x00000001
# define CMD_END			0x00000002
# define CMD_INPUT			0x00000004
# define CMD_TRUNC			0x00000008
# define CMD_APPEND			0x00000010
# define CMD_ERROR			0x00000020

typedef struct	s_token
{
	char			*str;
	int				length;
	int				flag;
	struct s_token	*next;
}				t_token;

t_token			*token_new(char *str, int flag);
t_token			*token_last(t_token *head);
void			token_update(t_token *last, char *str);
void			token_push_back(t_token **head, char *str, int flag);
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
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_command	*next;
}				t_command;

t_command		*cmd_new();
void			cmd_update(t_command *cmd, char *str);
t_command		*cmd_last(t_command *head);
void			cmd_push_back(t_command **head);
void			cmd_delete_redir(t_command **head);

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
	pid_t		pid[MAX_COMMAND];
}				t_info;

void			init_info(t_info *info);
void			parse_env(t_info *info, char *envp[]);
char			**get_env_array(t_info *info);

void			sigint_handler(int signo);
void			sigquit_handler(int signo);

void			prompt(t_info *info);
void			replace_input(t_info *info);
void			tokenize(t_info *info);
void			token_to_command(t_info *info);
void			handle_fd(t_info *info);
void			execute(t_info *info);

void			fd_close(int fd);

#endif
