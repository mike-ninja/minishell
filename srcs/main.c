/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/19 17:45:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void check_args(t_args *args)
// {
// 	size_t index;

// 	index = -1;
// 	while (++index < args->len)
// 		ft_printf("%i [%s]\n", index, args->array[index]);
// }

static void	session_init(t_session *session)
{
	session->env = NULL;
	session->arg = NULL;
	session->pwd = NULL;
}

// static void print_print(t_session *session)
// {
// 	char **env;
// 	char **arg;

// 	env = session->env;
// 	arg = session->arg;
	
// 	ft_printf("Print ENV\n");
// 	while (*env)
// 	{
// 		ft_printf("%s\n", *env);
// 		env++;
// 	}
// 	ft_printf("Print ARG\n");
// 	while (*arg)
// 	{
// 		ft_printf("%s\n", *arg);
// 		arg++;
// 	}
// }

static int	system_call(t_session *sesh)
{
	pid_t	id;
	
	id = fork();
	if (id < 0)
		return (0);
	else if (id == 0)
		execve(*sesh->arg, sesh->arg, sesh->env);
	else
		wait(&id);
	return (1);
}

int	main(void)
{
	char		*line;
	t_session	sesh[1];

	line = NULL;
	session_init(sesh);
	sesh->env = env_init();
	while (1)
	{
		ft_printf("$> ");
		if (get_next_line(0, &line))
		{
			sesh->arg = get_args(line);
			if (!built_ins(sesh))
			{	
				if (ft_strcmp(*sesh->arg, "exit") == 0)
					return(ft_exit(sesh, "exit\n"));
				if (!system_call(sesh))
					return(ft_exit(sesh, "Fork Failed\n"));
			}
			arg_clean(sesh->arg, line);
		}
	}
	return(SUCCESS);
}
