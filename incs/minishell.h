/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/29 15:29:18 by mbarutel         ###   ########.fr       */
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

# define SUCCESS 1
# define FAILURE 0
# define PROMPT "$> "
# define MAXPATHLEN 1024

extern int errno ; // Delete this when no longer used

typedef struct sesssion
{
	char	**env;
	char	**arg;
	// char	*pwd;
}				t_session;

/* Functions for Environment Variables */
int		env_len(char **env);
int		env_print(char **env);
char	**env_init(void);
int		set_env(t_session *session, char *env);
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
int		ft_exit(t_session *session, char *message);
void	arg_clean(char **arg, char *line);

/* Changing directory */
int		ft_cd(t_session *sesh);

/* Printing header */
void	header_print(void);

/* Confirming file exists */
char	*confirm_addr(char *addr, char *file);

/* Cycle */
char	**cycle(t_session *sesh, char *line);
// t_session *cycle(t_session *sesh, char *line);

#endif
