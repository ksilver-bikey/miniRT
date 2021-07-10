/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 11:53:11 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/13 11:53:12 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	point_line_dist(double point[3], t_vec *vec)
{
	double	res[3];

	res[0] = (vec->start[1] - point[1]) * vec->vec[2] -\
									vec->vec[1] * (vec->start[2] - point[2]);
	res[1] = -1 * ((vec->start[0] - point[0]) * vec->vec[2] -\
									vec->vec[0] * (vec->start[2] - point[2]));
	res[2] = vec->vec[0] * (vec->start[1] - point[1]) -\
									(vec->start[0] - point[0]) * vec->vec[1];
	return (vec_len(res) / vec->len);
}

double	pln_line_sin(double vec1[3], double vec2[3])
{
	return (ft_mod_db(vec_scalar_mp(vec1, vec2)) /\
											(vec_len(vec1) * vec_len(vec2)));
}

void	point_line_perp(t_vec *line, double point[3], double perp_base[3])
{
	double	len;
	double	coef;

	len = vec_len(line->vec);
	coef = line->vec[0] * (line->start[0] - point[0]) + line->vec[1] *\
	(line->start[1] - point[1]) + line->vec[2] * (line->start[2] - point[2]);
	coef /= len;
	perp_base[0] = line->start[0] - coef * line->vec[0] / len;
	perp_base[1] = line->start[1] - coef * line->vec[1] / len;
	perp_base[2] = line->start[2] - coef * line->vec[2] / len;
}

double	line_line_dist(t_vec *vec1, t_vec *vec2)
{
	double tmp[3];

	tmp[0] = vec1->vec[1] * vec2->vec[2] - vec2->vec[1] * vec1->vec[2];
	tmp[1] = -1 * (vec1->vec[0] * vec2->vec[2] - vec2->vec[0] * vec1->vec[2]);
	tmp[2] = vec1->vec[0] * vec2->vec[1] - vec2->vec[0] * vec1->vec[1];
	return (ft_mod_db((vec1->vec[0] * (vec2->vec[1] * (vec2->start[2] -\
	vec1->start[2]) - (vec2->start[1] - vec1->start[1]) * vec2->vec[2]) -\
	vec2->vec[0] * (vec1->vec[1] * (vec2->start[2] - vec1->start[2]) -\
	(vec2->start[1] - vec1->start[1]) * vec1->vec[2]) + (vec2->start[0] -\
	vec1->start[0]) * (vec1->vec[1] * vec2->vec[2] - vec2->vec[1] *\
	vec1->vec[2]))) / vec_len(tmp));
}

void	fill_normalize(t_vec *vec, t_vec *new)
{
	double	div;

	div = 1.0 / vec->len;
	new->vec[0] = vec->vec[0] * div;
	new->vec[1] = vec->vec[1] * div;
	new->vec[2] = vec->vec[2] * div;
	triple_copy(new->start, vec->start);
	triple_copy(new->end, new->start);
	triple_summ(new->end, new->vec);
	new->len = 1.0;
}
