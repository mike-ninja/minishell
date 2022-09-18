/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/17 19:34:10 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	garbage_collect(t_args *args)
{
	while (args->len--)
		free(args->array[args->len]);
	free(args->array);
	free(args);
}

// static void check_args(t_args *args)
// {
// 	size_t len;

// 	len = args->len;
// 	while (len--)
// 		ft_printf("%s\n", args->array[len]);
// 	ft_printf("This happens\n");
// }

int	main(void)
{
	pid_t	id;
	char	*line;
	t_env	*env;
	t_args	*args;

	line = NULL;
	args = NULL;
	env = NULL;
	env = env_init(env);
	while (1)
	{
		ft_printf("$> ");	
		if (get_next_line(0, &line))
		{
			args = get_args(line);
			if (!built_ins(args, env))
			{	
				id = fork();
				if (id < 0)
				{
					ft_printf("Fork failed\n");
					exit(FAILURE);
				}
				else if (id == 0) // Sometimes it works, sometimes it doesn't
					execve(args->array[0], args->array, NULL);
				else
					wait(&id);
				garbage_collect(args);
			}
			if (ft_strcmp(*args->array, "exit") == 0)
				return(ft_exit(env, SUCCESS));
		}
	}
	return(SUCCESS);
}
