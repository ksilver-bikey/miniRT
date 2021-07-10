/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:31:50 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:31:51 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	mrt_fill_vector(double *start, double *end, t_vec *new)
{
	new->start[0] = start[0];
	new->start[1] = start[1];
	new->start[2] = start[2];
	new->end[0] = end[0];
	new->end[1] = end[1];
	new->end[2] = end[2];
	new->vec[0] = end[0] - start[0];
	new->vec[1] = end[1] - start[1];
	new->vec[2] = end[2] - start[2];
	new->len = vec_len(new->vec);
}

void	mrt_fill_vector_less(double *start, double *end, t_vec *new)
{
	new->start[0] = start[0];
	new->start[1] = start[1];
	new->start[2] = start[2];
	new->end[0] = end[0];
	new->end[1] = end[1];
	new->end[2] = end[2];
	new->vec[0] = end[0] - start[0];
	new->vec[1] = end[1] - start[1];
	new->vec[2] = end[2] - start[2];
}

int		vec_codir(double *vec1, double *vec2)
{
	if ((vec1[0] / vec2[0]) < -0.000000000001)
		return (0);
	if ((vec1[1] / vec2[1]) < -0.000000000001)
		return (0);
	if ((vec1[2] / vec2[2]) < -0.000000000001)
		return (0);
	return (1);
}

int		vectors_codirection(double point[3], t_vec *line)
{
	double	zyx[3];

	return (vec_codir(xyz(point[0] - line->start[0], point[1] - line->start[1],\
	point[2] - line->start[2], zyx), line->vec));
}

t_vec	*mrt_make_vector(double *start, double *end)
{
	t_vec *new;

	if (!(new = (t_vec *)malloc(sizeof(t_vec))))
		mrt_canalize();
	mrt_fill_vector(start, end, new);
	return (new);
}
