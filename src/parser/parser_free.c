/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:50:09 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/22 21:57:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr && arr[i])
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	free_close_util(char *line, int file)
{
	if (line)
		free(line);
	close_protect(file);
}

void	close_protect(int file)
{
	if (file != 0)
	{
		if (close(file) == -1)
			error_msg("closing file errored");
	}
}

void	free_objects(t_data *data)
{
	int		i;

	i = 0;
	if (data->objs && data->objs[i])
	{
		while (data->objs[i])
		{
			free(data->objs[i]);
			i++;
		}
	}
	free(data->objs);
}
