/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:40:37 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:40:41 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	cyl_ray_angle_two(t_cyl *cyl, t_vec *line, double point[3],\
														double light_cmp[2])
{
	if (cyl->last_point == 0)
		return (cyl_side_angle(cyl, line, point));
	if (cyl->last_point == 1)
		return (cyl_top_angle(cyl, line, light_cmp[0]));
	if (cyl->last_point == 2)
		return (cyl_bot_angle(cyl, line, light_cmp[1]));
	return (-2.0);
}

double	cyl_ray_angle(double cam[3], t_cyl *cyl, t_vec *line, double point[3])
{
	double	light_cmp[2];

	light_cmp[0] = plain_point_cmp(line->end, &cyl->top);
	light_cmp[1] = plain_point_cmp(line->end, &cyl->bot);
	if (cyl->camera == 'i')
	{
		if (light_cmp[0] * cyl->top_cmp < 0.0 || light_cmp[1] * cyl->bot_cmp\
			< 0.0 || point_line_dist(line->end, &cyl->vector) > cyl->rd + 1e-12)
			return (-2.0);
	}
	if (cyl->camera == 'o')
	{
		if (light_cmp[0] * cyl->top_cmp > 0.0 && light_cmp[1] * cyl->bot_cmp\
		> 0.0 && point_line_dist(line->end, &cyl->vector) < cyl->rd - 1e-12)
			return (-2.0);
	}
	return (cyl_ray_angle_two(cyl, line, point, light_cmp));
	if (cam[0] != cam[0])
		cam[0] += 0.1;
}

t_cyl	*make_cyl(double dm_hg[3], double crd[3], double norm[3],\
														unsigned char color[4])
{
	t_cyl	*cyl;
	int		cnt;
	double	zyx[3];

	cnt = 3;
	cyl = (t_cyl *)malloc_gc(sizeof(t_cyl));
	cyl->rd = dm_hg[0] * 0.5;
	cyl->height = dm_hg[1] * 0.5;
	while (--cnt > -1)
		cyl->crds[cnt] = crd[cnt];
	while (++cnt < 4)
		cyl->color[cnt] = color[cnt];
	mrt_fill_vector(cyl->crds, xyz(crd[0] + norm[0], crd[1] + norm[1], crd[2] +\
	norm[2], zyx), &cyl->vector);
	cyl->angle_coords = cyl_line_coords;
	cyl->ray_angle = cyl_ray_angle;
	cyl->type = 'c';
	cylinder_s_top(cyl);
	return (cyl);
}

int		cyl_bot(t_cyl *cyl, t_vec *line, double bot_point[3])
{
	plain_line_coords(&cyl->bot, line, bot_point);
	if (bot_point[0] != bot_point[0] || \
		point_line_dist(bot_point, &cyl->vector) > cyl->rd || \
		point_plain_dist(bot_point, &cyl->bot) > 1e-11)
		return (0);
	if (vectors_codirection(bot_point, line) == 0)
		return (0);
	if (plain_point_cmp(bot_point, &cyl->bot) / cyl->bot_cmp < -1e-11)
		return (0);
	if (point_point_dist(bot_point, cyl->crds) > cyl->ins_area + 1e-11)
		return (0);
	return (1);
}

int		cyl_top(t_cyl *cyl, t_vec *line, double top_point[3])
{
	plain_line_coords(&cyl->top, line, top_point);
	if (top_point[0] != top_point[0] || \
		point_line_dist(top_point, &cyl->vector) > cyl->rd || \
		point_plain_dist(top_point, &cyl->top) > 1e-11)
		return (0);
	if (vectors_codirection(top_point, line) == 0)
		return (0);
	if (plain_point_cmp(top_point, &cyl->top) / cyl->top_cmp < -1e-11)
		return (0);
	if (point_point_dist(top_point, cyl->crds) > cyl->ins_area + 1e-11)
		return (0);
	return (1);
}
