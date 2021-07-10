/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_reading_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:07:58 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:07:59 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	mrt_square_read(char *line)
{
	char			**data;
	double			crds[3];
	unsigned char	color[4];
	double			norm_vec[3];
	double			size;

	data = ft_split(line, ' ');
	if (data[0] == NULL || data[1] == NULL || data[2] == NULL ||\
		data[3] == NULL || data[4] == NULL)
		mrt_input_error(5, line);
	if (mrt_read_coords(data[1], crds) == 0)
		mrt_input_error(9, line);
	if (mrt_read_coords(data[2], norm_vec) == 0)
		mrt_input_error(10, line);
	if (mrt_read_block(data[3]) == 0)
		mrt_input_error(5, line);
	size = ft_atod(data[3]);
	if (mrt_read_color(data[4], color) == 0)
		mrt_input_error(11, line);
	if (data[5] != NULL)
		mrt_input_error(5, line);
	obj_add_to_scene((t_mro *)make_square(crds, norm_vec, color, size));
	mrt_reading_data_clean(data);
}

void	mrt_triangle_read(char *line)
{
	char			**data;
	double			crds[3][3];
	unsigned char	color[4];

	data = ft_split(line, ' ');
	if (data[0] == NULL || data[1] == NULL || data[2] == NULL ||\
		data[3] == NULL || data[4] == NULL)
		mrt_input_error(5, line);
	if (mrt_read_coords(data[1], crds[0]) == 0)
		mrt_input_error(9, line);
	if (mrt_read_coords(data[2], crds[1]) == 0)
		mrt_input_error(9, line);
	if (mrt_read_coords(data[3], crds[2]) == 0)
		mrt_input_error(9, line);
	if (mrt_read_color(data[4], color) == 0)
		mrt_input_error(11, line);
	if (data[5] != NULL)
		mrt_input_error(5, line);
	obj_add_to_scene((t_mro *)make_triangle(crds[0], crds[1], crds[2], color));
	mrt_reading_data_clean(data);
}

void	mrt_plane_read(char *line)
{
	char			**data;
	double			crds[3];
	unsigned char	color[4];
	double			norm_vec[3];

	data = ft_split(line, ' ');
	if (data[0] == NULL || data[1] == NULL || data[2] == NULL ||\
		data[3] == NULL)
		mrt_input_error(5, line);
	if (mrt_read_coords(data[1], crds) == 0)
		mrt_input_error(9, line);
	if (mrt_read_coords(data[2], norm_vec) == 0)
		mrt_input_error(10, line);
	if (mrt_read_color(data[3], color) == 0)
		mrt_input_error(11, line);
	if (data[4] != NULL)
		mrt_input_error(5, line);
	mrt_norm_vec(norm_vec, line);
	obj_add_to_scene((t_mro *)make_pln_o(crds, norm_vec, color));
	mrt_reading_data_clean(data);
}

void	mrt_light_read(char *line)
{
	char			**data;
	double			coords[3];
	unsigned char	color[4];
	double			intense;

	data = ft_split(line, ' ');
	if (data[0] == NULL || data[1] == NULL || data[2] == NULL ||\
		data[3] == NULL)
		mrt_input_error(5, line);
	if (mrt_read_coords(data[1], coords) == 0)
		mrt_input_error(9, line);
	if (mrt_read_block(data[2]) == 0)
		mrt_input_error(5, line);
	intense = ft_atod(data[2]);
	if (intense > 1.0 || intense < 0.0)
		mrt_input_error(17, line);
	if (mrt_read_color(data[3], color) == 0)
		mrt_input_error(11, line);
	if (data[4] != NULL)
		mrt_input_error(5, line);
	fiat_lux(coords, color, intense);
	mrt_reading_data_clean(data);
}

void	mrt_sphere_read(char *line)
{
	char			**data;
	double			crds[3];
	double			dm;
	unsigned char	color[4];

	data = ft_split(line, ' ');
	if (data[0] == NULL || data[1] == NULL || data[2] == NULL ||\
		data[3] == NULL)
		mrt_input_error(5, line);
	if (mrt_read_coords(data[1], crds) == 0)
		mrt_input_error(9, line);
	if (mrt_read_block(data[2]) == 0)
		mrt_input_error(5, line);
	if (mrt_read_color(data[3], color) == 0)
		mrt_input_error(11, line);
	if (data[4] != NULL)
		mrt_input_error(5, line);
	if ((dm = ft_atod(data[2])) < 0.0)
		mrt_input_error(14, line);
	obj_add_to_scene((t_mro *)make_sph(crds, dm, color));
	mrt_reading_data_clean(data);
}
