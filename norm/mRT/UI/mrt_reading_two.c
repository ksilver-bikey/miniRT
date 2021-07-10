/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_reading_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:09:58 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 11:10:00 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	mrt_add_read(char *line)
{
	char	**data;

	data = ft_split(line, ' ');
	if (ft_strncmp(data[1], "an", 3) == 0)
		fg_win()->auto_normalization = 1;
	mrt_reading_data_clean(data);
}

void	obj_add_to_scene(t_mro *obj)
{
	t_mro	*runner;

	if ((runner = fg_win()->objects) == NULL)
	{
		fg_win()->objects = obj;
		return ;
	}
	while (runner->next != NULL)
		runner = runner->next;
	runner->next = obj;
}

void	mrt_cylinder_read(char *line)
{
	char			**data;
	double			crds[2][3];
	double			dm_hg[3];
	unsigned char	color[4];

	data = ft_split(line, ' ');
	if (data[0] == NULL || data[1] == NULL || data[2] == NULL ||\
		data[3] == NULL || data[4] == NULL || data[5] == NULL)
		mrt_input_error(5, line);
	if (mrt_read_coords(data[1], crds[0]) == 0)
		mrt_input_error(9, line);
	if (mrt_read_coords(data[2], crds[1]) == 0)
		mrt_input_error(10, line);
	if (mrt_read_color(data[3], color) == 0)
		mrt_input_error(11, line);
	if (mrt_read_block(data[4]) == 0 || mrt_read_block(data[5]) == 0)
		mrt_input_error(5, line);
	dm_hg[0] = ft_atod(data[4]);
	dm_hg[1] = ft_atod(data[5]);
	if (dm_hg[0] <= 0.0 || dm_hg[1] <= 0.0 || data[6] != NULL)
		mrt_input_error(5, line);
	mrt_norm_vec(crds[1], line);
	obj_add_to_scene((t_mro *)make_cyl(dm_hg, crds[0], crds[1], color));
	mrt_reading_data_clean(data);
}

void	camera_add_to_scene(t_obj_cam *camera)
{
	t_obj_cam *tmp;

	camera->num = 0;
	if (fg_win()->camera == NULL)
	{
		fg_win()->camera = camera;
		return ;
	}
	tmp = fg_win()->camera;
	while (tmp->next != NULL)
	{
		camera->num++;
		tmp = tmp->next;
	}
	tmp->next = camera;
	camera->prev = tmp;
	fg_win()->camera->prev = camera;
}

void	mrt_camera_read(char *line)
{
	char		**data;
	double		crds[3];
	double		fov;
	double		norm_vec[3];

	data = ft_split(line, ' ');
	if (data[0] == NULL || data[1] == NULL || data[2] == NULL ||\
		data[3] == NULL)
		mrt_input_error(5, line);
	if (fg_win()->x == 0 || fg_win()->y == 0)
		return ((void)mrt_no_res_cam_buff(line));
	if (mrt_read_coords(data[1], crds) == 0)
		mrt_input_error(9, line);
	if (mrt_read_coords(data[2], norm_vec) == 0)
		mrt_input_error(10, line);
	fov = ft_atod(data[3]);
	if (mrt_read_block(data[3]) != (int)ft_strlen(data[3]) || fov < 1)
		mrt_input_error(12, line);
	if (data[4] != NULL)
		mrt_input_error(5, line);
	mrt_norm_vec(norm_vec, line);
	(fov == 180.0) ? fov = 179.0 : 1;
	camera_add_to_scene(make_camera(crds, fov, norm_vec));
	mrt_reading_data_clean(data);
}
