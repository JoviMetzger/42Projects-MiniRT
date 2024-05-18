/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:02:19 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/18 18:08:54 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

int	handle_texture(t_data *data, char *str)
{
	mlx_texture_t	*texture;

	str = give_null(str);
	texture = mlx_load_png(str);
	if (!texture)
		return (0);
	data->objs[data->objs_i]->texture = texture;
	return (1);
}

/**
 * @brief	takes array of strings from read_file()
 * 			checks the elements and values are correct
 * 			converts from string to double/int etc..
 * 			adds them to the t_data struct
 * 			if something wrong, function will free, error and exit
 * 			will not return here if error
 * @brief	(check elements + validate_elems) 
 * 			while input is in string format, check it's validity
 * 			Ambient light, Light and Camera must be declared and only once
 * 			all other elements (sp, cy, pl) must be declared, poss multi
 * 			if error/invalid, free in check function, error and exit
 * 			number of arguments and characters checked before conversion
*/
static void	parse_array(t_data *data, char **arr)
{
	int			obj_count;

	check_elements(arr);
	obj_count = validate_elems(arr);
	convert_cap_input(data, arr);
	convert_obj_input(data, arr, obj_count);
}

/**
 * @brief	read through the file line by line, copying each
 * 			line into a 2D array of strings (arr)
 * 			if error occurs, array and line is freed, file is closed,
 * 			error message and exit
 * 			else close file, call parse_array which checks input, converts it
 * 			and adds everything into t_data struct, 
 * 			then frees array and line and returns to main to continue
 * 			rt_malloc is protected :)
*/
static void	read_file(t_data *data, int file)
{
	char	*line;
	char	**arr;
	int		i;

	i = 0;
	line = get_next_line(file);
	arr = rt_malloc(NULL, BUFF_SIZE, file);
	while (line && i < BUFF_SIZE)
	{
		if (line)
		{
			arr[i] = ft_strdup(line);
			if (!arr[i])
				free_close_parse_error("malloc failure", arr, line, file);
			free(line);
			line = get_next_line(file);
			i++;
		}
	}
	arr[i] = NULL;
	free_close_util(line, file);
	parse_array(data, arr);
	free_array(arr);
}

static void	check_file_type(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (is_dot(arg[i]))
		{
			if (ft_strcmp(&arg[i], ".rt") == 0)
				return ;
			else
				error_msg("wrong file type");
		}
		i++;
	}
	error_msg("wrong file type");
}

void	init_mouse_map(t_data *data) 
{
	int16_t	**map;
	uint32_t	i;

	i = 0;
	data->mouse.window_h = HEIGHT;
	data->mouse.window_w = WIDTH;
	data->mouse.selected = false;
	if (data->mouse.mouse_map != NULL)
		error_msg("map failure");
	map = map_malloc((data->mouse.window_h + 1) * sizeof(int16_t *));
	data->mouse.mouse_map = map;
	while (i < data->mouse.window_h)
	{
		map[i] = map_malloc(data->mouse.window_w  * sizeof(int16_t));
		i++;
	}
	map[i] = NULL;
	data->mouse.mouse_map = map;
}

void	parse_input(int argc, char **argv, t_data *data)
{
	int		file;

	file = 0;
	ft_bzero(data, sizeof(t_data));
	if (argc != 2)
		error_msg("wrong number of arguments");
	data->i_am = -1;
	check_file_type(argv[1]);
	file = open(argv[1], O_RDONLY, 0644);
	if (file == -1)
		error_msg("couldn't open file");
	read_file(data, file);
	init_mouse_map(data);
}
