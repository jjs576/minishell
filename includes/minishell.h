/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:58:02 by jjoo              #+#    #+#             */
/*   Updated: 2021/01/16 21:44:01 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>

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

# define INFO_WAITING		0x00000001
# define INFO_EXIT			0x00000002
# define INFO_DONT_EXEC		0x00000004

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
	char				**argv;
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
	int			in;
	int			out;
	char		pwd[MAX_PATH_LENGTH];
	char		oldpwd[MAX_PATH_LENGTH];
	char		input[MAX_STR];
	int			input_len;
	int			command_num;
	int			returned;
	int			status;
	int			exit_return;
	pid_t		pid[MAX_COMMAND];
	int			pipefd[MAX_COMMAND][2];
}				t_info;

void			parse_env(t_info *info, char *envp[]);
char			**get_env_array(t_info *info);

t_info			*signal_info(t_info *input);
void			signal_handler(int signo);

void			prompt(t_info *info);
void			replace_input(t_info *info);
void			tokenize(t_info *info);
void			token_to_command(t_info *info);
void			handle_fd(t_info *info);
void			execute(t_info *info);

void			close_fd(int fd);
void			free_2d(char **p);
void			init_info(t_info *info);
void			init_info_input(t_info *info);
void			clear_info(t_info *info);

int				connect_fd(t_command *cmd, int fd[MAX_COMMAND][2], int index);
void			wait_forked(t_info *info);
char			*get_correct_path(char *path, char *file);
char			*get_absolute_path(t_info *info, t_command *cmd);

void			print_error(char *cmd, int error);

void			ft_echo(t_info *info, t_command *cmd);
void			ft_pwd(t_info *info);
void			ft_cd(t_info *info, t_command *cmd);
void			ft_exit(t_info *info, t_command *cmd);
void			ft_unset(t_info *info, t_command *cmd);
void			ft_export(t_info *info, t_command *cmd);
void			ft_env(t_info *info, t_command *cmd);

#endif
