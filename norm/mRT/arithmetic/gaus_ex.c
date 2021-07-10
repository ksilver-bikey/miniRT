/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaus_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:29:36 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:29:37 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	gaus_sort(t_gaus *(*line)[3])
{
	int	weight[3];
	int cnt;

	cnt = -1;
	while (++cnt < 3)
		weight[cnt] = 0;
	while (--cnt > -1)
	{
		if ((*line)[cnt]->s_un == 0.0)
			weight[cnt] = 2;
		else if ((*line)[cnt]->f_un == 0.0)
			weight[cnt] = 1;
	}
	while (++cnt < 3)
	{
		if (weight[cnt] == 2 && cnt != 2)
			gaus_sort_rev(line, 2, cnt);
		if (weight[cnt] == 1 && cnt != 1)
			gaus_sort_rev(line, 1, cnt);
	}
	if ((*line)[0]->f_un == 0.0)
		gaus_one_more_thing(line, 0);
}

void	gaus_ex(t_gaus *fr, t_gaus *se, t_gaus *th, double result[3])
{
	t_gaus *line[3];

	line[0] = fr;
	line[1] = se;
	line[2] = th;
	gaus_sort(&line);
	fr_st(&line, 0, 1);
	fr_st(&line, 0, 2);
	se_st(&line, 1, 2);
	if (line[2]->t_un != 0.0)
		result[2] = line[2]->free / line[2]->t_un;
	else
		result[2] = 0.0;
	if (line[1]->s_un != 0.0)
		result[1] = (-1.0 * line[1]->t_un * result[2] + line[1]->free) /\
																line[1]->s_un;
	else
		result[1] = 0.0;
	if (line[0]->f_un != 0.0)
		result[0] = (-1.0 * (line[0]->s_un * result[1] + line[0]->t_un *\
		result[2]) + line[0]->free) / line[0]->f_un;
	else
		result[0] = 0.0;
}

void	gaus_fill(double f_s_t[3], double free, t_gaus *gau)
{
	gau->f_un = f_s_t[0];
	gau->s_un = f_s_t[1];
	gau->t_un = f_s_t[2];
	gau->free = free;
}

void	perp_lines_vec(t_vec *vec1, t_vec *vec2, double res[3])
{
	res[0] = vec1->vec[1] * vec2->vec[2] - vec2->vec[1] * vec1->vec[2];
	res[1] = -1 * (vec1->vec[0] * vec2->vec[2] - vec2->vec[0] * vec1->vec[2]);
	res[2] = vec1->vec[0] * vec2->vec[1] - vec2->vec[0] * vec1->vec[1];
}

t_vec	*perp_line(t_vec *vec1, t_vec *vec2, t_vec *res)
{
	double	perp[3];
	double	zyx[3][3];
	t_gaus	gau[3];

	perp_lines_vec(vec1, vec2, perp);
	gaus_fill(xyz(vec1->vec[0], -1.0 * vec2->vec[0], -1.0 * perp[0], zyx[0]),\
	-1.0 * (vec1->start[0] - vec2->start[0]), &gau[0]);
	gaus_fill(xyz(vec1->vec[1], -1.0 * vec2->vec[1], -1.0 * perp[1], zyx[0]),\
	-1.0 * (vec1->start[1] - vec2->start[1]), &gau[1]);
	gaus_fill(xyz(vec1->vec[2], -1.0 * vec2->vec[2], -1.0 * perp[2], zyx[0]),\
	-1.0 * (vec1->start[2] - vec2->start[2]), &gau[2]);
	gaus_ex(&gau[0], &gau[1], &gau[2], zyx[0]);
	mrt_fill_vector(xyz(vec1->vec[0] * zyx[0][0] + vec1->start[0],\
	vec1->vec[1] * zyx[0][0] + vec1->start[1], vec1->vec[2] * zyx[0][0] +\
	vec1->start[2], zyx[1]), xyz(vec2->vec[0] * zyx[0][1] +\
	vec2->start[0], vec2->vec[1] * zyx[0][1] + vec2->start[1], vec2->vec[2]\
	* zyx[0][1] + vec2->start[2], zyx[2]), res);
	return (res);
}
