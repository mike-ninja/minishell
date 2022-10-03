/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/03 10:20:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include "../libft/incs/ft_printf.h"

/* Mandatory */
# include	<sys/stat.h>

/* Bonus */
# include	<sys/ioctl.h>

# define RESET 0
# define FAIL 1
# define NOACC -1
# define NOEXI -2
# define PROMPT "$> "
# define MAXPATHLEN 1024
# define STARTCYCLE 0
# define ENDCYCLE 1

extern int errno ; // Delete this when no longer used

typedef struct sesssion
{
	char	**env;
	char	**arg;
	bool	tmp_env;
	int		result;
	// char	*pwd;
}				t_session;

/* Initialising Environment Variables */
char	**env_init(void);
char	**mandatory_env(t_session *sesh);
char	*shlvl(char *my_env, char *env);

/* Functions for Environment Variables */
int		array_len(char **env);
int		env_print(t_session *sesh);
int		set_env(t_session *session);
int		unset_env(t_session *session);
char	**env_get_var(t_session *sesh, char *key);
char	**env_last_prog(char *path, t_session *sesh);
int		append_env(t_session *sesh, char **arg);

/* Parsing through user input */
char	**get_args(t_session *sesh, char **line);
char	**dollar_parse(t_session *sesh);
char	**tilda_parse(t_session *sesh);

/* Parse through built in functions */
int		built_ins(t_session *session);

/* EXIT */
void	env_clean(char **env);
void	ft_exit(t_session *session, char *message, int status);
void	arg_clean(char **arg, char *line);

/* Changing directory */
int		ft_cd(t_session *sesh);

/* Printing header */
void	header_print(void);

/* Confirming file exists */
char	*confirm_addr(char *addr, char *file, int check);
int		check_addr(char *addr, char *file, char **buf);

/* Cycle */
char	**cycle(t_session *sesh, char *line, int position);

/* Binary execution */
int		system_call(t_session *sesh, char *file);

#endif
