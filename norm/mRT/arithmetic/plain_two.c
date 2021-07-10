/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:37:12 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:37:17 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int		plain_line_coords(t_pln *pln, t_vec *vec, double empty_point[3])
{
	double common_param;
	double equation;

	common_param = pln->norm[0] * vec->vec[0] + pln->norm[1] * vec->vec[1] +\
	pln->norm[2] * vec->vec[2];
	equation = (vec->start[0] + pln->x) * pln->norm[0] + \
	(vec->start[1] + pln->y) * pln->norm[1] +\
	(vec->start[2] + pln->z) * pln->norm[2];
	if (common_param == 0)
		return (0);
	common_param = (-1) * equation / common_param;
	empty_point[0] = vec->vec[0] * common_param + vec->start[0];
	empty_point[1] = vec->vec[1] * common_param + vec->start[1];
	empty_point[2] = vec->vec[2] * common_param + vec->start[2];
	return (1);
}

double	plain_point_cmp(double coords[3], t_pln *pln)
{
	return (((coords[0] + pln->x) * pln->norm[0]) + ((coords[1] + pln->y) *\
	pln->norm[1]) + ((coords[2] + pln->z) * pln->norm[2]));
}
