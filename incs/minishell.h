/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/02 07:56:25 by mbarutel         ###   ########.fr       */
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

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1
# define PROMPT "$> "
# define MAXPATHLEN 1024

extern int errno ; // Delete this when no longer used

typedef struct sesssion
{
	char	**env;
	char	**arg;
	bool	tmp_env;
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

/* Cycle */
char	**cycle(t_session *sesh, char *line);

/* Binary execution */
int		system_call(t_session *sesh, char *file);

#endif
