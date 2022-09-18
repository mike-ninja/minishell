/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/17 11:09:31 by mbarutel         ###   ########.fr       */
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

typedef struct env
{
	char		*key;
	char		*val;
	struct env	*next;
}				t_env;

typedef struct	args
{
	size_t	len;
	char	**array;
}				t_args;

/*Functions for Environment Variables*/
t_env	*env_node(void);
int		env_print(t_env *env);
t_env	*env_init(t_env *env_head);
int		set_env(t_env *env, char **input);
int		unset_env(t_env *env, char **input);
// void	env_delete(t_env *env);

/*Parsing through user input*/
t_args	*get_args(char *line);
// t_input	*get_args(char *line);
// void	print_args(t_input *head); // delete when no longer used

/*Parse through built in functions*/
bool	built_ins(t_args *args, t_env *env);

/*EXIT*/
int		ft_exit(t_env *env, int status);

#endif
