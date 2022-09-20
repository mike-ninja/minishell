/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/20 12:46:11 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include "../libft/incs/ft_printf.h"

# define SUCCESS 0
# define FAILURE 1

// Fetch terminal size
# include <sys/ioctl.h>

// typedef struct 	env
// {
// 	size_t	len;
// 	char	**array;
// }				t_env;

// typedef struct	args
// {
// 	size_t	len;
// 	char	**array;
// }				t_args;

typedef struct	sesssion
{
	char	**env;
	char	**arg;
	char	*pwd;
	int		status;
	// char	*las_exec;
}				t_session;

/*Functions for Environment Variables*/
// t_env	*env_node(void);
size_t	env_len(char **env);
int		env_print(char **env);
void	env_clean(char **env);
char	**env_init(void);
int 	set_env(t_session *session);
int		unset_env(t_session *session);
// void	env_delete(t_env *env);

/*Parsing through user input*/
// t_args  *args_init(void);
char	**get_args(char *line);
// // t_input	*get_args(char *line);
// // void	print_args(t_input *head); // delete when no longer used

// /*Parse through built in functions*/
bool	built_ins(t_session *session);

/*EXIT*/
int		ft_exit(t_session *session, char *message);
void	arg_clean(char **arg, char *line);

/*cd*/
int		ft_cd(t_session *sesh);

#endif
