/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/16 13:39:50 by mbarutel         ###   ########.fr       */
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

/*Functions for Environment Variables*/
t_env	*env_node(void);
int		env_print(t_env *env);
t_env	*env_init(t_env *env_head);
int		set_env(t_env *env, char **input);
int		unset_env(t_env *env, char **input);

/*Parse through built in functions*/
bool	built_ins(char **input, t_env *env);


#endif
