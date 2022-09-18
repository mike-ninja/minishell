/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:55:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/18 16:57:19 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_args(t_input *head)
// {
// 	while (head)
// 	{
// 		ft_printf("[%s]\n", head->str);
// 		head = head->next;	
// 	}
// }

// char	*qoute_sep(char **line)
// {
// 	int		qou_pos;
// 	char	*ret;
	
// 	ret = NULL;
// 	qou_pos = 0;
// 	while (line[0][qou_pos] && line[0][qou_pos] != '"')
// 		qou_pos++;
// 	ret = (char *)malloc(qou_pos + 1);
// 	if (!ret)
// 		return (NULL);
// 	ret[qou_pos] = '\0';
// 	ft_strncpy(ret, line[0], qou_pos);
// 	line[0] = &line[0][qou_pos];
// 	return(ret);
// }

static size_t	get_index_position(char *line, size_t index)
{
	index++;
	while (line[index] != '"' && line[index])
		index++;
	return(index);
}

// static void	init_arg_struct(t_args *ret, size_t len)
// {
// 	ret->array = (char **)malloc(sizeof(char *) * len + 1);
// 	if (!ret->array)
// 		ret->array = NULL;
// 	ret->len = len;
// }

static size_t	arg_len(char *line)
{
	size_t	len;
	size_t	index;

	len = 0;
	index = 0;
	while (line[index] != '\0')
	{
		if (line[index] == '"')
		{
			len++;	
			index = get_index_position(line, index);
		}
		if (line[index] != ' ' && index == 0)
				len++;
		if (index)
			if (line[index] != ' ' && line[index - 1] == ' ')
				len++;
		index++;
	}
	return (len);
}

char	**get_args(char *line) // It needs to be done via char **
{
	char	**args;
	char	**ptr;
	size_t	len;
	

	len = arg_len(line);
	args = (char **)malloc(sizeof(char *) * len + 1);
	if (!args)
		return (NULL);
	ptr = args;
	args[len] = NULL;
	while (len--)
	{
		// ft_printf("This happens\n");
		while (ft_iswhitespace(*line))
			line++;
		if (*line == '"')
		{
			line++;
			*args = ft_strdup(ft_strsep(&line, "\""));
		}
		else
			*args = ft_strdup(ft_strsep(&line, " "));
		args++;
	}
	return (ptr);
}
