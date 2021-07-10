/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:42:39 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:42:41 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int		square_line_angle_coords(t_sqr *sqr, t_vec *line, double point[3])
{
	plain_line_coords(&sqr->pln_s, line, point);
	if ((point_line_dist(point, &sqr->line[0]) < sqr->size + 0.000000000000001)\
	&& (point_line_dist(point, &sqr->line[1]) < sqr->size + 0.000000000000001)\
	&& (point_line_dist(point, &sqr->line[2]) < sqr->size + 0.000000000000001)\
	&& (point_line_dist(point, &sqr->line[3]) < sqr->size + 0.000000000000001))
	{
		if (vectors_codirection(point, line) == 1)
			return (1);
	}
	return (-2);
}

double	sqr_ray_angle(double cam[3], t_sqr *sqr, t_vec *line, double point[3])
{
	double	cam_cmp;
	double	light_cmp;

	light_cmp = plain_point_cmp(line->end, &sqr->pln_s);
	cam_cmp = plain_point_cmp(cam, &sqr->pln_s);
	if (light_cmp * cam_cmp > 0.0)
		return (pln_line_sin(line->vec, sqr->pln_s.norm));
	return (-2.0);
	if (point[0] != point[0])
		point[0] += 0.1;
}
