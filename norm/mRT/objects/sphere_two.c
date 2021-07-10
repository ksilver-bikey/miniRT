/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:41:17 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:41:25 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	sphere_ray_angle(double cam[3], t_sph *sph,\
												t_vec *line, double point[3])
{
	t_pln	plain;
	t_vec	plain_norm;
	double	temp[3];
	double	light_dist;

	light_dist = point_point_dist(line->end, sph->crd);
	if (sph->camera == 'i')
		if (light_dist > sph->rd + 0.000000000001)
			return (-2.0);
	if (sph->camera == 'o')
		if (light_dist < sph->rd + 0.000000000001)
			return (-2.0);
	mrt_fill_vector(point, sph->crd, &plain_norm);
	fill_plain_eq_norm(&plain_norm, point, &plain);
	temp[0] = plain_point_cmp(sph->crd, &plain);
	temp[1] = plain_point_cmp(line->end, &plain);
	if (sph->camera == 'i')
		return (pln_line_sin(line->vec, plain.norm));
	if (temp[0] * temp[1] > -0.000000000001)
		return (-2.0);
	return (pln_line_sin(line->vec, plain.norm));
	if (cam[0] != cam[0])
		cam[0] += 0.1;
}
