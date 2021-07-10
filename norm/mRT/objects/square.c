/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:42:05 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:42:07 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	side_vector_k(t_sqr *new, double side_vector[3])
{
	double	normalizer;

	side_vector[0] = 1.0;
	if (new->pln_s.norm[1] == 0.0)
	{
		side_vector[1] = 1.0;
		side_vector[0] = 0.0;
	}
	else
		side_vector[1] = -1 * new->pln_s.norm[0] / new->pln_s.norm[1];
	side_vector[2] = 0.0;
	normalizer =\
	sqrt(side_vector[0] * side_vector[0] + side_vector[1] * side_vector[1] \
		+ side_vector[2] * side_vector[2]);
	side_vector[0] = side_vector[0] / normalizer * new->size * 0.5;
	side_vector[1] = side_vector[1] / normalizer * new->size * 0.5;
	side_vector[2] = side_vector[2] / normalizer * new->size * 0.5;
}

void	top_vector_k(t_sqr *new, double top_vector[3], double normalizer)
{
	if (new->pln_s.norm[2] == 0.0)
	{
		top_vector[0] = 0.0;
		top_vector[1] = 0.0;
		top_vector[2] = 1.0;
	}
	else if (new->pln_s.norm[0] == 0.0 && new->pln_s.norm[1] == 0.0)
	{
		top_vector[0] = 1.0;
		top_vector[1] = 0.0;
		top_vector[2] = 0.0;
	}
	else
	{
		top_vector[0] = new->pln_s.norm[0];
		top_vector[1] = new->pln_s.norm[1];
		top_vector[2] = -1 * (sq_pw(new->pln_s.norm[0]) +\
								sq_pw(new->pln_s.norm[1])) / new->pln_s.norm[2];
	}
	normalizer = sqrt(top_vector[0] * top_vector[0] + top_vector[1] *\
	top_vector[1] + top_vector[2] * top_vector[2]);
	top_vector[0] = top_vector[0] / normalizer * new->size * 0.5;
	top_vector[1] = top_vector[1] / normalizer * new->size * 0.5;
	top_vector[2] = top_vector[2] / normalizer * new->size * 0.5;
}

void	sq_points_calc(t_sqr *new, double side_vector[3], double top_vector[3])
{
	double	zyx[2][3];
	int		k;

	triple_diff(new->corners[2], side_vector);
	triple_summ(new->corners[2], top_vector);
	triple_summ(new->corners[3], side_vector);
	triple_summ(new->corners[3], top_vector);
	triple_diff(new->corners[0], side_vector);
	triple_diff(new->corners[0], top_vector);
	triple_summ(new->corners[1], side_vector);
	triple_diff(new->corners[1], top_vector);
	mrt_fill_vector(new->corners[0], new->corners[1], &new->line[0]);
	mrt_fill_vector(new->corners[2], new->corners[3], &new->line[1]);
	k = 0;
	if (vec_len(xyz(new->corners[0][0] - new->corners[2][0], new->corners[0][1]\
		- new->corners[2][1], new->corners[0][2] - new->corners[2][2], zyx[0]))\
		> vec_len(xyz(new->corners[0][0] - new->corners[3][0],\
		new->corners[0][1] - new->corners[3][1], new->corners[0][2] -\
												new->corners[3][2], zyx[1])))
		k = 1;
	mrt_fill_vector(new->corners[0], new->corners[2 + k], &new->line[2]);
	mrt_fill_vector(new->corners[1], new->corners[3 - k], &new->line[3]);
}

void	corner_points_k(t_sqr *new)
{
	double	side_vector[3];
	double	top_vector[3];
	int		cnt;

	cnt = -1;
	side_vector_k(new, side_vector);
	top_vector_k(new, top_vector, 0.0);
	while (++cnt < 4)
		triple_summ(new->corners[cnt], new->crds);
	sq_points_calc(new, side_vector, top_vector);
}

t_sqr	*make_square(double point[3], double vec[3], unsigned char color[4],\
												double size)
{
	t_sqr	*new;
	int		cnt;

	new = (t_sqr *)malloc_gc(sizeof(t_sqr));
	new->angle_coords = square_line_angle_coords;
	cnt = -1;
	while (++cnt < 3)
		new->crds[cnt] = point[cnt];
	while (--cnt > -1)
		new->pln_s.norm[cnt] = vec[cnt];
	while (++cnt < 4)
		new->color[cnt] = color[cnt];
	new->pln_s.x = -1.0 * point[0];
	new->pln_s.y = -1.0 * point[1];
	new->pln_s.z = -1.0 * point[2];
	new->type = 'k';
	new->size = size;
	new->ray_angle = sqr_ray_angle;
	corner_points_k(new);
	return (new);
}
