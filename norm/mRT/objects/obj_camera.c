/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:41:46 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:41:49 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void		cam_point_calc_y(t_obj_cam *new, double side_vector[3],\
														double top_vector[3])
{
	triple_diff(new->screen_point[0], side_vector);
	triple_summ(new->screen_point[0], top_vector);
	triple_summ(new->screen_point[2], side_vector);
	triple_summ(new->screen_point[2], top_vector);
	triple_diff(new->screen_point[1], side_vector);
	triple_diff(new->screen_point[1], top_vector);
	triple_summ(new->screen_point[3], side_vector);
	triple_diff(new->screen_point[3], top_vector);
}

void		corner_points_z(t_obj_cam *new)
{
	double	side_vector[3];
	double	top_vector[3];
	int		cnt;

	cnt = -1;
	side_vector_z(side_vector, new->cam_vec);
	top_vector_z(top_vector, new->cam_vec);
	while (++cnt < 4)
		triple_summ(new->screen_point[cnt], new->field_center);
	if ((new->cam_vec[0] == 0.0 && new->cam_vec[1] == 0.0 && new->cam_vec[2]\
					< 0.0) || (new->cam_vec[0] + new->cam_vec[1] != 0.0 &&\
														new->cam_vec[2] > 0.0))
	{
		cam_point_calc_y(new, side_vector, top_vector);
		left_right_corner(new->screen_point[1], new->screen_point[0], new);
		left_right_corner(new->screen_point[3], new->screen_point[2], new);
	}
	else
	{
		cam_point_calc_z(new, side_vector, top_vector);
		left_right_corner(new->screen_point[0], new->screen_point[1], new);
		left_right_corner(new->screen_point[2], new->screen_point[3], new);
	}
	mrt_fill_vector(new->crds, new->screen_point[0], &new->temp_vec);
}

int			cam_next_step(t_obj_cam *cam)
{
	int	res;

	res = 0;
	if (cam->act_step[0] < fg_win()->x - 1)
	{
		triple_summ(cam->temp_vec.end, cam->ray_step_h);
		cam->act_step[0]++;
		res = 1;
		cam->act_step[2]++;
	}
	else if (cam->act_step[1] < fg_win()->y - 1)
	{
		cam->act_step[0] = 0;
		cam->screen_point[0][0] += cam->ray_step_v[0];
		cam->screen_point[0][1] += cam->ray_step_v[1];
		cam->screen_point[0][2] += cam->ray_step_v[2];
		triple_copy(cam->temp_vec.end, cam->screen_point[0]);
		cam->act_step[1]++;
		res = 1;
		cam->act_step[2]++;
	}
	mrt_fill_vector(cam->crds, cam->temp_vec.end, &cam->temp_vec);
	fill_normalize(&cam->temp_vec, &cam->act_vec);
	return (res);
}

t_obj_cam	*make_camera(double crds[3], double fov, double cam_vec[3])
{
	t_obj_cam	*new;
	int			cnt;
	double		add_c;

	if (!(new = (t_obj_cam *)malloc_gc(sizeof(t_obj_cam))))
		mrt_canalize();
	cnt = -1;
	while (++cnt < 3)
		new->crds[cnt] = crds[cnt];
	while (--cnt > -1)
		new->cam_vec[cnt] = cam_vec[cnt];
	new->fov = fov;
	new->next = NULL;
	new->type = 'C';
	add_c = ((double)fg_win()->x / 2000.0) / tan(fov * 0.5 *\
													3.14159265358979 / 180);
	while (++cnt < 3)
		new->field_center[cnt] = (crds[cnt] + cam_vec[cnt] * add_c);
	cnt = fg_win()->x * fg_win()->y;
	new->field = (int *)malloc_gc(cnt * sizeof(int));
	corner_points_z(new);
	cam_step(new);
	new->step = cam_next_step;
	new->act_step[2] = 0;
	return (new);
}
