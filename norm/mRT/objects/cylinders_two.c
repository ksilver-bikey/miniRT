/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:40:29 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:40:33 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	cylinder_s_top(t_cyl *cyl)
{
	t_vec	tmp;
	double	zyx[3];

	fill_normalize(&cyl->vector, &tmp);
	fill_plain_eq_norm(&tmp, xyz(cyl->crds[0] + tmp.vec[0] * cyl->height,\
		cyl->crds[1] + tmp.vec[1] * cyl->height, cyl->crds[2] + tmp.vec[2] *\
		cyl->height, zyx), &cyl->top);
	fill_plain_eq_norm(&tmp, xyz(cyl->crds[0] - tmp.vec[0] * cyl->height,\
		cyl->crds[1] - tmp.vec[1] * cyl->height, cyl->crds[2] - tmp.vec[2] *\
		cyl->height, zyx), &cyl->bot);
	cyl->ins_area = sqrt(sq_pw(cyl->rd) + sq_pw(cyl->height));
	cyl->top_cmp = plain_point_cmp(cyl->crds, &cyl->top);
	cyl->bot_cmp = plain_point_cmp(cyl->crds, &cyl->bot);
}

void	cylinder_s_plain(t_cyl *cyl, t_vec *line)
{
	double	top_cmp;
	double	bot_cmp;

	top_cmp = plain_point_cmp(line->start, &cyl->top);
	bot_cmp = plain_point_cmp(line->start, &cyl->bot);
	if (top_cmp * cyl->top_cmp < 0.0 || bot_cmp * cyl->bot_cmp < 0.0)
	{
		cyl->camera = 'o';
		return ;
	}
	if (point_point_dist(line->start, cyl->crds) > cyl->ins_area)
		cyl->camera = 'o';
	else if (point_line_dist(line->start, &cyl->vector) > cyl->rd)
		cyl->camera = 'o';
	else
		cyl->camera = 'i';
}

double	cyl_top_angle(t_cyl *cyl, t_vec *line, double light_cmp)
{
	if (cyl->camera == 'i')
		return (pln_line_sin(line->vec, cyl->top.norm));
	if (light_cmp * cyl->top_cmp > 0.0)
		return (-2.0);
	return (pln_line_sin(line->vec, cyl->top.norm));
}

double	cyl_bot_angle(t_cyl *cyl, t_vec *line, double light_cmp)
{
	if (cyl->camera == 'i')
		return (pln_line_sin(line->vec, cyl->bot.norm));
	if (light_cmp * cyl->bot_cmp > 0.0)
		return (-2.0);
	return (pln_line_sin(line->vec, cyl->bot.norm));
}

double	cyl_side_angle(t_cyl *cyl, t_vec *line, double point[3])
{
	t_pln	plain;
	t_vec	plain_norm;
	double	temp[3];
	double	angle;

	point_line_perp(&cyl->vector, point, temp);
	mrt_fill_vector(point, temp, &plain_norm);
	fill_plain_eq_norm(&plain_norm, point, &plain);
	temp[0] = plain_point_cmp(cyl->crds, &plain);
	temp[1] = plain_point_cmp(line->end, &plain);
	angle = pln_line_sin(line->vec, plain.norm);
	if (cyl->camera == 'i')
		return (angle);
	if (temp[0] * temp[1] > 1e-12)
		return (-2.0);
	return (pln_line_sin(line->vec, plain.norm));
}
