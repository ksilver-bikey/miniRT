/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:42:50 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 13:42:52 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	triple_summ(double main[3], double additional[3])
{
	main[0] += additional[0];
	main[1] += additional[1];
	main[2] += additional[2];
}

void	triple_diff(double main[3], double additional[3])
{
	main[0] -= additional[0];
	main[1] -= additional[1];
	main[2] -= additional[2];
}

void	triple_copy(double main[3], double additional[3])
{
	main[0] = additional[0];
	main[1] = additional[1];
	main[2] = additional[2];
}

double	two_rays_angle(double vec1[3], double vec2[3])
{
	return (vec_scalar_mp(vec1, vec2) / (vec_len(vec1) * vec_len(vec2)));
}
