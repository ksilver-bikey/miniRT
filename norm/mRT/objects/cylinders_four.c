/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:40:46 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:40:48 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	cyl_side_one(double side_point[3], t_vec *tmp, double inside_cyl_len)
{
	side_point[0] += tmp->vec[0] * inside_cyl_len;
	side_point[1] += tmp->vec[1] * inside_cyl_len;
	side_point[2] += tmp->vec[2] * inside_cyl_len;
}

void	cyl_side_two(double side_point[3], t_vec *tmp, double inside_cyl_len)
{
	side_point[0] -= tmp->vec[0] * inside_cyl_len;
	side_point[1] -= tmp->vec[1] * inside_cyl_len;
	side_point[2] -= tmp->vec[2] * inside_cyl_len;
}

int		cyl_side(t_cyl *cyl, t_vec *line, t_vec *perp, double side_point[3])
{
	t_vec	tmp;
	double	angle;
	double	projection_len;
	double	inside_cyl_len;

	fill_normalize(line, &tmp);
	projection_len = sqrt(ft_mod_db(sq_pw(cyl->rd) - sq_pw(perp->len)));
	if (cyl->proj_len > 0.0 && projection_len > cyl->ins_area)
		projection_len = cyl->proj_len;
	cyl->proj_len = projection_len;
	angle = sqrt(1 - sq_pw(pln_line_sin(tmp.vec, cyl->top.norm)));
	inside_cyl_len = projection_len / angle;
	triple_copy(side_point, perp->start);
	if (inside_cyl_len != inside_cyl_len)
		inside_cyl_len = cyl->rd;
	(cyl->camera == 'i') ? (cyl_side_one(side_point, &tmp, inside_cyl_len)) :\
	(cyl_side_two(side_point, &tmp, inside_cyl_len));
	mrt_fill_vector(side_point, cyl->crds, &tmp);
	if ((side_point[0] != side_point[0]) || \
		(vectors_codirection(side_point, line) == 0) || \
	(point_point_dist(side_point, cyl->crds) > cyl->ins_area + 1e-10) ||\
	(plain_point_cmp(side_point, &cyl->top) / cyl->top_cmp < -1e-10) ||\
	(plain_point_cmp(side_point, &cyl->bot) / cyl->bot_cmp < -1e-10))
		return (0);
	return (1);
}

int		to_top_or_not_to_top(t_cyl *cyl, t_vec *line)
{
	static t_cyl	*remember_cyl = NULL;
	static double	remember_cam_x = 0.0;
	static double	remember_cam_y = 0.0;
	static double	remember_cam_z = 0.0;

	if (remember_cyl != cyl || remember_cam_x != line->start[0] ||\
		remember_cam_y != line->start[1] || remember_cam_z != line->start[2])
	{
		remember_cyl = cyl;
		remember_cam_x = line->start[0];
		remember_cam_y = line->start[1];
		remember_cam_z = line->start[2];
		return (1);
	}
	return (0);
}

int		tw_points_cmp(double point1[3], double point2[3])
{
	if (point1[0] - point2[0] > 0.00000000000001)
		return (0);
	if (point1[1] - point2[1] > 0.00000000000001)
		return (0);
	if (point1[2] - point2[2] > 0.00000000000001)
		return (0);
	return (1);
}
