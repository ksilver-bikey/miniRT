/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:37:40 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:37:42 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	*xyz(double x, double y, double z, double *xyz)
{
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
	return (xyz);
}

void	vec_normalize(double vec[3], double res[3])
{
	double	div;

	div = 1 / vec_len(vec);
	res[0] = vec[0] * div;
	res[1] = vec[1] * div;
	res[2] = vec[2] * div;
}

void	mrt_canalize(void)
{
	free_all();
	exit(0);
	return ;
}

double	sq_pw(double num)
{
	return (num * num);
}
