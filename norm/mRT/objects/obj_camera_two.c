/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_camera_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:41:56 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:41:57 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	side_vector_z(double side_vector[3], double cam[3])
{
	double normalizer;

	side_vector[0] = 1.0;
	if (cam[1] == 0.0)
	{
		side_vector[1] = 1.0;
		side_vector[0] = 0.0;
	}
	else
		side_vector[1] = -1.0 * cam[0] / cam[1];
	side_vector[2] = 0.0;
	normalizer =\
	sqrt(side_vector[0] * side_vector[0] + side_vector[1] * side_vector[1] \
		+ side_vector[2] * side_vector[2]);
	side_vector[0] = side_vector[0] / normalizer * (double)fg_win()->x / 2000.0;
	side_vector[1] = side_vector[1] / normalizer * (double)fg_win()->x / 2000.0;
	side_vector[2] = side_vector[2] / normalizer * (double)fg_win()->x / 2000.0;
}

void	top_vector_z(double top_vector[3], double cam[3])
{
	double normalizer;

	if (cam[2] == 0.0)
	{
		top_vector[0] = 0.0;
		top_vector[1] = 0.0;
		top_vector[2] = 1.0;
	}
	else if (cam[0] == 0.0 && cam[1] == 0.0)
	{
		top_vector[0] = 1.0;
		top_vector[1] = 0.0;
		top_vector[2] = 0.0;
	}
	else
	{
		top_vector[0] = cam[0];
		top_vector[1] = cam[1];
		top_vector[2] = -1 * (cam[0] * cam[0] + cam[1] * cam[1]) / cam[2];
	}
	normalizer = sqrt(top_vector[0] * top_vector[0] + top_vector[1] *\
	top_vector[1] + top_vector[2] * top_vector[2]);
	top_vector[0] = top_vector[0] / normalizer * (double)fg_win()->y / 2000.0;
	top_vector[1] = top_vector[1] / normalizer * (double)fg_win()->y / 2000.0;
	top_vector[2] = top_vector[2] / normalizer * (double)fg_win()->y / 2000.0;
}

void	left_right_corner(double left[3], double right[3], t_obj_cam *new)
{
	double	temp[3];

	if ((new->crds[0] == new->field_center[0]) && (((new->crds[1] < \
		new->field_center[1]) && (left[0] > right[0])) || ((new->crds[1] >\
								new->field_center[1]) && (left[0] < right[0]))))
	{
		triple_copy(temp, left);
		triple_copy(left, right);
		triple_copy(right, temp);
	}
	else if (((new->crds[0] < new->field_center[0]) && (left[1] < right[1])) ||\
		((new->crds[0] > new->field_center[0]) && (left[1] > right[1])))
	{
		triple_copy(temp, left);
		triple_copy(left, right);
		triple_copy(right, temp);
	}
}

void	cam_step(t_obj_cam *new)
{
	double	div;

	div = 1.0 / (double)fg_win()->x;
	new->ray_step_h[0] = new->screen_point[1][0] - new->screen_point[0][0];
	new->ray_step_h[1] = new->screen_point[1][1] - new->screen_point[0][1];
	new->ray_step_h[2] = new->screen_point[1][2] - new->screen_point[0][2];
	new->ray_step_h[0] *= div;
	new->ray_step_h[1] *= div;
	new->ray_step_h[2] *= div;
	div = 1.0 / (double)fg_win()->y;
	new->ray_step_v[0] = new->screen_point[2][0] - new->screen_point[0][0];
	new->ray_step_v[1] = new->screen_point[2][1] - new->screen_point[0][1];
	new->ray_step_v[2] = new->screen_point[2][2] - new->screen_point[0][2];
	new->ray_step_v[0] *= div;
	new->ray_step_v[1] *= div;
	new->ray_step_v[2] *= div;
	triple_copy(new->temp_vec.end, new->screen_point[0]);
	mrt_fill_vector(new->crds, new->temp_vec.end, &new->temp_vec);
	fill_normalize(&new->temp_vec, &new->act_vec);
}

void	cam_point_calc_z(t_obj_cam *new, double side_vector[3],\
														double top_vector[3])
{
	triple_diff(new->screen_point[1], side_vector);
	triple_summ(new->screen_point[1], top_vector);
	triple_summ(new->screen_point[0], side_vector);
	triple_summ(new->screen_point[0], top_vector);
	triple_diff(new->screen_point[3], side_vector);
	triple_diff(new->screen_point[3], top_vector);
	triple_summ(new->screen_point[2], side_vector);
	triple_diff(new->screen_point[2], top_vector);
}
