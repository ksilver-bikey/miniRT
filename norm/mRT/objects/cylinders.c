/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:40:23 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:40:25 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int		cyl_return(double temp_point[3][3], t_vec *line, int angle[3], int res)
{
	double	len[3];
	double	temp;
	int		cnt;

	cnt = -1;
	while (++cnt < 3)
		if (angle[cnt] > 0)
			len[cnt] = point_point_dist(line->start, temp_point[cnt]);
		else
			len[cnt] = 0;
	while (--cnt > -1)
		if (len[cnt] > 0)
		{
			temp = len[cnt];
			res = cnt;
		}
	while (++cnt < 3)
		if (temp > len[cnt] && angle[cnt] > 0)
			if (tw_points_cmp(temp_point[cnt], line->start) == 0)
			{
				temp = len[cnt];
				res = cnt;
			}
	return (res);
}

int		cyl_line_coords(t_cyl *cyl, t_vec *line, double *point)
{
	t_vec	perp;
	double	temp_point[3][3];
	int		temp;
	int		angle[3];

	if ((point_line_dist(cyl->crds, line) > cyl->rd + cyl->height) || \
		(line_line_dist(line, &cyl->vector) > cyl->rd + 0.0000000000001) ||\
		(point_line_dist(cyl->crds, line) > cyl->ins_area + 0.00000000000001))
		return (-2);
	if (to_top_or_not_to_top(cyl, line) == 1)
		cylinder_s_plain(cyl, line);
	perp_line(line, &cyl->vector, &perp);
	angle[0] = cyl_side(cyl, line, &perp, temp_point[0]);
	angle[1] = cyl_top(cyl, line, temp_point[1]);
	angle[2] = cyl_bot(cyl, line, temp_point[2]);
	if ((angle[0] + angle[1] + angle[2]) < 1)
		return (-1);
	temp = cyl_return(temp_point, line, angle, 5);
	triple_copy(point, temp_point[temp]);
	cyl->last_point = temp;
	return (1);
}
