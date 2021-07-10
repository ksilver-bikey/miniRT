/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:31:43 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 13:31:45 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	fill_the_field(t_obj_cam *cam, char in_out, t_mro *act, t_mro *mem)
{
	t_pixel_step	memory;
	t_pixel_step	new;
	unsigned char	color[4];

	mrt_color_null(color);
	while (act != NULL)
	{
		new.a_c_answer = act->angle_coords(act, &cam->act_vec, new.point);
		if (new.a_c_answer > 0)
		{
			new.len = point_point_dist(new.point, cam->crds);
			if (new.len > 0.0 && (new.len < memory.len || in_out == 'o'))
			{
				ftf_point_copy(&memory, &new);
				mrt_copy_color(act->color, color);
				in_out = (ftf_point_copy(&memory, &new) ? 'i' : 'i');
				mem = act;
			}
		}
		act = act->next;
	}
	if (mem != NULL)
		et_lux_fit(&memory, color, mem, cam);
	cam->field[cam->act_step[2]] = mrt_int_color(color);
}

void	walk_through_the_field(t_obj_cam *cam)
{
	int			check;

	if (cam == NULL)
		mrt_input_error(15, NULL);
	while (cam != NULL)
	{
		fg_win()->act_cam = cam;
		check = 1;
		while (check == 1)
		{
			fill_the_field(cam, 'o', fg_win()->objects, NULL);
			check = cam->step(cam);
		}
		cam = cam->next;
	}
}
