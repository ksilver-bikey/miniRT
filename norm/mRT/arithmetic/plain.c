/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:37:28 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:37:35 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	point_plain_dist(double point[3], t_pln *pln)
{
	return (ft_mod_db(plain_point_cmp(point, pln)) / sqrt(sq_pw(pln->norm[0])\
								+ sq_pw(pln->norm[1]) + sq_pw(pln->norm[2])));
}

t_pln	*make_plain_eq_norm(t_vec *vec, double point[3])
{
	t_pln	*pln;

	if (!(pln = (t_pln *)malloc(sizeof(t_pln))))
		mrt_canalize();
	pln->x = -1.0 * point[0];
	pln->y = -1.0 * point[1];
	pln->z = -1.0 * point[2];
	pln->norm[0] = vec->vec[0];
	pln->norm[1] = vec->vec[1];
	pln->norm[2] = vec->vec[2];
	return (pln);
}

void	fill_plain_eq_norm(t_vec *vec, double point[3], t_pln *pln)
{
	pln->x = -1.0 * point[0];
	pln->y = -1.0 * point[1];
	pln->z = -1.0 * point[2];
	pln->norm[0] = vec->vec[0];
	pln->norm[1] = vec->vec[1];
	pln->norm[2] = vec->vec[2];
}

void	fill_plain_equation(double point[3], double vec1[3], double vec2[3],\
																	t_pln *pln)
{
	pln->x = -1.0 * point[0];
	pln->y = -1.0 * point[1];
	pln->z = -1.0 * point[2];
	pln->norm[0] = (vec1[1] * vec2[2] - vec1[2] * vec2[1]);
	pln->norm[1] = -1 * (vec1[0] * vec2[2] - vec1[2] * vec2[0]);
	pln->norm[2] = (vec1[0] * vec2[1] - vec1[1] * vec2[0]);
}

t_pln	*make_plain_equation(double point[3], double vec1[3], double vec2[3])
{
	t_pln	*pln;

	if (!(pln = (t_pln *)malloc(sizeof(t_pln))))
		mrt_canalize();
	fill_plain_equation(point, vec1, vec2, pln);
	return (pln);
}
