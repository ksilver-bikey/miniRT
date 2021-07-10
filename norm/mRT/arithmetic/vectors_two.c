/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:31:56 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:31:59 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	vec_scalar_mp(double vec1[3], double vec2[3])
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

double	vec_cos(double vec1[3], double vec2[3])
{
	return (ft_mod_db(vec_scalar_mp(vec1, vec2) / (vec_len(vec1)\
															* vec_len(vec2))));
}

double	vec_len(double vec[3])
{
	return (sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2])));
}

double	point_point_dist(double point1[3], double point2[3])
{
	double	zyx[3];

	return (vec_len(xyz(point1[0] - point2[0], point1[1] - point2[1],\
												point1[2] - point2[2], zyx)));
}

void	vec_scolar(double vec1[3], double vec2[3], double tmp[3])
{
	tmp[0] = vec1[1] * vec2[2] - vec2[1] * vec1[2];
	tmp[1] = -1 * (vec1[0] * vec2[2] - vec2[0] * vec1[2]);
	tmp[2] = vec1[0] * vec2[1] - vec2[0] * vec1[1];
}
