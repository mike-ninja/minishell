/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/19 13:17:58 by mbarutel         ###   ########.fr       */
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

int	main(void)
{
	pid_t		id;
	char		*line;
	t_session	session[1];

	line = NULL;
	session_init(session);
	session->env = env_init();
	while (1)
	{
		ft_printf("$> ");
		if (get_next_line(0, &line))
		{
			session->arg = get_args(line);
			if (!built_ins(session))
			{	
				// ft_printf("Running another functions\n");
				if (ft_strcmp(*session->arg, "exit") == 0)
					return(ft_exit(session, "exit\n"));
				id = fork();
				if (id < 0)
					return(ft_exit(session, "Fork Failed\n"));
				else if (id == 0)
					execve(*session->arg, session->arg, session->env);
				else
					wait(&id);
			}
			arg_clean(session->arg, line);
		}
	}
	return(SUCCESS);
}
