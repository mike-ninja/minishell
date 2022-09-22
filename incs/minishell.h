/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/22 15:26:55 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include "../libft/incs/ft_printf.h"

/* Bonus */
# include	<sys/ioctl.h>

# include	<sys/stat.h>

# define	SUCCESS 1
# define	FAILURE 0
# define	PROMPT "$> "

extern int errno ; // Delete this when no longer used


typedef struct	sesssion
{
	char	**env;
	char	**arg;
	char	*pwd;
	// char	*las_exec;
}				t_session;

/* Functions for Environment Variables */
size_t	env_len(char **env);
int		env_print(char **env);
char	**env_init(void);
int 	set_env(t_session *session);
int		unset_env(t_session *session);
char	**env_get_var(t_session *sesh, char *key);

/* Parsing through user input */
char	**get_args(char **line);

/* Parse through built in functions */
bool	built_ins(t_session *session);

/* EXIT */
void	env_clean(char **env);
int		ft_exit(t_session *session, char *message);
void	arg_clean(char **arg, char *line);

/* Changing directory */
int		ft_cd(t_session *sesh);

/* Printing header */
void	header_print(void);

#endif
