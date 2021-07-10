/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaus_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:29:43 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:29:45 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	gaus_sort_rev(t_gaus *(*line)[3], int num, int cnt)
{
	t_gaus *temp;

	temp = (*line)[num];
	(*line)[num] = (*line)[cnt];
	(*line)[cnt] = temp;
}

void	gaus_one_more_thing(t_gaus *(*line)[3], int cnt)
{
	while (++cnt < 3)
	{
		if ((*line)[cnt]->f_un != 0.0 && (*line)[cnt]->s_un != 0.0)
			gaus_sort_rev(line, 0, cnt);
	}
}

void	fr_st(t_gaus *(*line)[3], int top, int bot)
{
	double	temp;

	temp = (*line)[bot]->f_un;
	(*line)[bot]->f_un *= (*line)[top]->f_un;
	(*line)[bot]->s_un *= (*line)[top]->f_un;
	(*line)[bot]->t_un *= (*line)[top]->f_un;
	(*line)[bot]->free *= (*line)[top]->f_un;
	(*line)[bot]->f_un -= (*line)[top]->f_un * temp;
	(*line)[bot]->s_un -= (*line)[top]->s_un * temp;
	(*line)[bot]->t_un -= (*line)[top]->t_un * temp;
	(*line)[bot]->free -= (*line)[top]->free * temp;
}

void	se_st(t_gaus *(*line)[3], int top, int bot)
{
	double	temp;

	temp = (*line)[bot]->s_un;
	(*line)[bot]->s_un *= (*line)[top]->s_un;
	(*line)[bot]->t_un *= (*line)[top]->s_un;
	(*line)[bot]->free *= (*line)[top]->s_un;
	(*line)[bot]->s_un -= (*line)[top]->s_un * temp;
	(*line)[bot]->t_un -= (*line)[top]->t_un * temp;
	(*line)[bot]->free -= (*line)[top]->free * temp;
}
