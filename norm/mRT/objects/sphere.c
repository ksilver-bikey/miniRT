/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:42:24 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:42:26 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_sph			*make_sph(double crd[3], double diameter,\
														unsigned char color[4])
{
	t_sph	*sphere;
	int		cnt;

	if (!(sphere = (t_sph *)malloc_gc(sizeof(t_sph))))
		mrt_canalize();
	sphere->rd = diameter * 0.5;
	sphere->crd[0] = crd[0];
	sphere->crd[1] = crd[1];
	sphere->crd[2] = crd[2];
	sphere->angle_coords = sphere_line_coords;
	sphere->type = 's';
	sphere->ray_angle = sphere_ray_angle;
	cnt = -1;
	while (++cnt < 4)
		sphere->color[cnt] = color[cnt];
	return (sphere);
}

int				alert_way(t_sph *sph, t_vec *line, double side_point[3])
{
	int		cnt;
	t_vec	tmp;

	cnt = -1;
	fill_normalize(line, &tmp);
	if (sph->camera == 'o')
		while (++cnt < 3)
			side_point[cnt] -= tmp.vec[cnt] * sph->rd;
	else
		while (++cnt < 3)
			side_point[cnt] += tmp.vec[cnt] * sph->rd;
	return (1);
}

int				sphere_side(t_sph *sph, t_vec *line, double ray_dist,\
														double side_point[3])
{
	double	inside_sph_len;
	t_vec	tmp;
	int		cnt;

	point_line_perp(line, sph->crd, side_point);
	if (ray_dist < 0.00000000000001)
		return (alert_way(sph, line, side_point));
	inside_sph_len = sqrt(sq_pw(sph->rd) - sq_pw(ray_dist));
	fill_normalize(line, &tmp);
	cnt = -1;
	if (sph->camera == 'o')
	{
		while (++cnt < 3)
			side_point[cnt] -= tmp.vec[cnt] * inside_sph_len;
		if (point_point_dist(side_point, sph->crd) > sph->rd + 0.000000000001)
			return (-2);
	}
	else
		while (++cnt < 3)
			side_point[cnt] += tmp.vec[cnt] * inside_sph_len;
	if (side_point[0] != side_point[0])
		return (-2);
	return (1);
}

static void		to_sph_or_not_to_sph(t_sph *sph, t_vec *line)
{
	static t_sph	*remember_sph = NULL;
	static double	remember_cam_x = 0.0;
	static double	remember_cam_y = 0.0;
	static double	remember_cam_z = 0.0;

	if (remember_sph != sph || remember_cam_x != line->start[0] ||\
		remember_cam_y != line->start[1] || remember_cam_z != line->start[2])
	{
		if (point_point_dist(line->start, sph->crd) > sph->rd + 1e-12)
			sph->camera = 'o';
		else
			sph->camera = 'i';
		remember_sph = sph;
		remember_cam_x = line->start[0];
		remember_cam_y = line->start[1];
		remember_cam_z = line->start[2];
	}
}

int				sphere_line_coords(t_sph *sph, t_vec *line, double point[3])
{
	double	ray_dist;
	double	temp_point[3];
	double	angle;

	to_sph_or_not_to_sph(sph, line);
	if ((ray_dist = point_line_dist(sph->crd, line)) >\
		sph->rd + 0.00000000000001)
		return (-2);
	angle = sphere_side(sph, line, ray_dist, temp_point);
	point[0] = temp_point[0];
	point[1] = temp_point[1];
	point[2] = temp_point[2];
	if (vectors_codirection(point, line) == 0 || angle < 1)
		return (-1);
	return (2);
}
