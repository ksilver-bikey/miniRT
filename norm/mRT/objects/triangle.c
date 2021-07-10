/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 23:52:53 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/13 23:52:54 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int			triangle_line_point(t_tri *tri, t_vec *line, double point[3])
{
	plain_line_coords(&tri->plain, line, point);
	if (vectors_codirection(point, line) == 0 ||\
						point_point_dist(point, tri->points[0]) > tri->max)
		return (-2);
	if ((plain_point_cmp(point, &tri->borders[0]) / tri->opposite[0]) < 0.0)
		return (-1);
	if ((plain_point_cmp(point, &tri->borders[1]) / tri->opposite[1]) < 0.0)
		return (-1);
	if ((plain_point_cmp(point, &tri->borders[2]) / tri->opposite[2]) < 0.0)
		return (-1);
	return (1);
}

void		triangle_opposites(t_tri *new)
{
	fill_plain_equation(new->points[0], new->lines[1].vec, new->lines[2].vec,\
																&new->plain);
	fill_plain_equation(new->points[0], new->lines[0].vec, new->plain.norm,\
															&new->borders[0]);
	fill_plain_equation(new->points[1], new->lines[1].vec, new->plain.norm,\
															&new->borders[1]);
	fill_plain_equation(new->points[2], new->lines[2].vec, new->plain.norm,\
															&new->borders[2]);
	new->opposite[0] = plain_point_cmp(new->points[2], &new->borders[0]);
	new->opposite[1] = plain_point_cmp(new->points[0], &new->borders[1]);
	new->opposite[2] = plain_point_cmp(new->points[1], &new->borders[2]);
}

double		tri_ray_angle(double cam[3], t_tri *tri,\
												t_vec *line, double point[3])
{
	double	cam_cmp;
	double	light_cmp;

	light_cmp = plain_point_cmp(line->end, &tri->plain);
	cam_cmp = plain_point_cmp(cam, &tri->plain);
	if (light_cmp * cam_cmp > -0.00000001)
		return (pln_line_sin(line->vec, tri->plain.norm));
	return (-2.0);
	if (point[0] != point[0])
		point[0] += 0.1;
}

t_tri		*make_triangle(double point_one[3], double point_two[3],\
								double point_three[3], unsigned char color[4])
{
	t_tri	*new;
	int		cnt;

	new = (t_tri *)malloc_gc(sizeof(t_tri));
	triple_copy(new->points[0], point_one);
	triple_copy(new->points[1], point_two);
	triple_copy(new->points[2], point_three);
	mrt_fill_vector(new->points[0], new->points[1], &new->lines[0]);
	mrt_fill_vector(new->points[1], new->points[2], &new->lines[1]);
	mrt_fill_vector(new->points[2], new->points[0], &new->lines[2]);
	cnt = 4;
	while (--cnt > -1)
		new->color[cnt] = color[cnt];
	new->angle_coords = triangle_line_point;
	new->ray_angle = tri_ray_angle;
	triangle_opposites(new);
	new->max = new->lines[0].len;
	new->type = 't';
	if (new->lines[1].len > new->max)
		new->max = new->lines[1].len;
	if (new->lines[2].len > new->max)
		new->max = new->lines[2].len;
	return (new);
}
