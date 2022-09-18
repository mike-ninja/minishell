/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:55:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/17 11:01:31 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_input	*arg_node(void) // Need deletion if malloc fails
// {
// 	t_input	*node;

// 	node = NULL;
// 	node = (t_input *)malloc(sizeof(t_input));
// 	if (!node)
// 		return (NULL);
// 	node->str = NULL;
// 	node->next = NULL;
// 	return (node);
// }

// void	print_args(t_input *head)
// {
// 	while (head)
// 	{
// 		ft_printf("[%s]\n", head->str);
// 		head = head->next;	
// 	}
// }

char	*qoute_sep(char **line)
{
	int		qou_pos;
	char	*ret;
	
	ret = NULL;
	qou_pos = 0;
	while (line[0][qou_pos] && line[0][qou_pos] != '"')
		qou_pos++;
	ret = (char *)malloc(qou_pos + 1);
	if (!ret)
		return (NULL);
	ret[qou_pos] = '\0';
	ft_strncpy(ret, line[0], qou_pos);
	line[0] = &line[0][qou_pos];
	return(ret);
}

static size_t	get_index_position(char *line, size_t index)
{
	index++;
	while (line[index] != '"' && line[index])
		index++;
	return(index);
}

static void	init_arg_struct(t_args *ret, size_t len)
{
	ret->array = (char **)malloc(sizeof(char *) * len);
	if (!ret->array)
		ret->array = NULL;
	ret->len = len;
}

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


t_args	*get_args(char *line) // It needs to be done via char **
{
	t_args	*ret;
	char	*ptr;
	size_t	len;
	size_t	index;
	
	ret = (t_args *)malloc(sizeof(t_arg));
	if (!ret)
		return (NULL);
	len = arg_len(line);
	init_arg_struct(ret, len);
	ptr = line;
	index = 0;
	while (len--)
	{
		while (ft_iswhitespace(*line))
			line++;
		if (*line == '"')
		{
			line++;
			ret->array[index] = ft_strdup(ft_strsep(&line, "\""));
		}
		else
			ret->array[index] = ft_strdup(ft_strsep(&line, " ")); // Maybe no need to strdup this?
		index++;
	}
	free(ptr);
	return (ret);
}
