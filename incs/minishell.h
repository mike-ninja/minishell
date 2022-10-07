/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/07 09:24:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include "../libft/incs/ft_printf.h"

/* Mandatory */
# include	<sys/stat.h>

#ifdef __linux__
# include	<sys/wait.h>
#endif

/* Bonus */
# include	<sys/ioctl.h>

# define RESET 0
# define ERROR 1
# define INVALID -1
# define NOACCESS -2
# define TOOMANYARGS -3
# define NOCOMMAND -4
# define ERR_NOMEM -5
# define START 0
# define END 1

# define PROMPT "$> "
# define MAXPATHLEN 1024
# define MAXARGLEN 256

typedef struct sesssion
{
	char	**env;
	char	**arg;
	char	*tmp_env;
	int		result;
}				t_session;

typedef struct dollar_attr
{
	int		i;
	bool	key;
	bool	match;
	char	**keys;
	bool	needle;
}				t_dollar;

/* Initialising Environment Variables */
char	**env_init(void);
char	**mandatory_env(t_session *sesh);
char	*shlvl(char *my_env, char *env);

/* Functions for Environment Variables */
int		array_len(char **env, bool pos);
char	**env_get_var(t_session *sesh, char *key);
char	**env_last_prog(char *path, t_session *sesh);
int		append_env(t_session *sesh, char **arg);
int		env_removal(t_session *sesh, char *env);

/* PARSER */
char	*get_extra(char **keys);
void	user_expansion(char **arg);
void	tilda_parse(t_session *sesh);
void	dollar_parse(t_session *sesh);
char	*prefix(char **arg, char *str);
int		get_args(t_session *sesh, char **line);
void	find_match_env(char **arg, char **env, t_dollar *attr);

/* Parse through built in functions */
int		built_ins(t_session *session);

/* EXIT */
void	env_clean(char **env);
void	ft_exit(t_session *session, char *message, int status);
void	arg_clean(char **arg);

/* Changing directory */
int		ft_cd(t_session *sesh);

/* Printing header */
void	header_print(void);

/* Confirming file exists */
int		check_addr(char *addr, char *file, char **buf);
int		check_address(char *file);

/* Cycle */
void	cycle(t_session *sesh, bool pos);

/* Binary execution */
int		system_call(t_session *sesh);

/* Error messages */
void	error_message(t_session *sesh);

/* Builtins */
int		cmd_echo(char **arg);
int		cmd_env(t_session *sesh);
int		cmd_setenv(t_session *session);
int		cmd_unsetenv(t_session *session);
int		cmd_cd(t_session *sesh);

/* Builtins Utils */
void	cd_success(t_session *sesh);

/* Utils */
char	*skip_whitespace(char *str);


#endif
