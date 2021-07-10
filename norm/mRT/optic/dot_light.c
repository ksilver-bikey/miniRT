/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 18:36:12 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/19 18:36:16 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light	*mrt_make_dot(double coords[3], double vec[3], t_dot_light_pack dlp)
{
	t_light	*new;
	t_vec	tmp;
	double	len;

	new = fiat_lux(coords, dlp.color, dlp.intens);
	new->type = 'd';
	mrt_fill_vector(xyz(0.0, 0.0, 0.0, new->ext_point), vec, &tmp);
	fill_plain_eq_norm(&tmp, xyz(coords[0] + vec[0], coords[1] + vec[1], \
						coords[2] + vec[2], new->ext_point), &new->plain);
	len = vec_len(vec);
	new->ext_rd = len * tan(dlp.light_angle * 0.5 * 3.14159265358979 / 180);
	return (new);
}

int		dot_light_gate(t_light *dot_l, t_vec *line)
{
	double	point[3];

	plain_line_coords(&dot_l->plain, line, point);
	if (point_point_dist(point, dot_l->ext_point) < dot_l->ext_rd)
		return (1);
	return (0);
}
